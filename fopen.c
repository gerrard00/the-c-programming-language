#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define PERMS 0666 /* RW for owner, group, others */

/* there's no OPEN_MAX on linux */
#define OPEN_MAX FOPEN_MAX

/* can't find these macros anywhere */
/* copied this from book */
enum flag {
  _READ = 01,     /* file open for reading */
  _WRITE = 02,    /* file open for writing */
  _UNBUF= 04,     /* file is unbuffered */
  _EOF= 010,      /* EOF has occurred on this file */
  _ERR= 020       /* error occurred on this file */
};

/* real FILE is undocumented, use this from k&r */
typedef struct iobuf{
  int cnt; /* characters left */
  char *ptr; /* next character position */
  char *base; /* location of buffer */
  int flag;/*mode of file access*/
  int fd;/*file descriptor*/
} MY_FILE;

MY_FILE _iob[OPEN_MAX] = { /* stdin, stdout, stderr */
  { 0, (char *) 0, (char *) 0, _READ, 0 },
  { 0, (char *) 0, (char *) 0, _WRITE, 1 },
  { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
};

#undef getc
#define getc(p)(--(p)->cnt >= 0 \
    ?(unsigned char) *(p)->ptr++ : _fillbuf(p))

MY_FILE *my_fopen(char *name, char *mode);
int _fillbuf(MY_FILE *fp);

int main()
{
  MY_FILE *file = my_fopen("fopen.c", "r");
  char c;

  c = getc(file);
  while((c = getc(file)) != EOF) {
    printf("%c", c);
  }
}

/* fopen: open file, return file ptr */
MY_FILE *my_fopen(char *name, char *mode)
{
  int fd;
  MY_FILE *fp;
  if (*mode != 'r' && *mode != 'w' && *mode != 'a') {
    return NULL;
  }
  for(fp = _iob; fp < _iob + OPEN_MAX; fp++) {
    if ((fp->flag & (_READ | _WRITE)) == 0) {
      break; /* found free slot */
    }
  }
  if (fp >= _iob + OPEN_MAX) { /* no free slots */
    return NULL;
  }

  if (*mode == 'w') {
    fd = creat(name, PERMS);
  } else if (*mode == 'a') {
    if ((fd = open(name, O_WRONLY, 0)) == -1) {
      fd = creat(name, PERMS);
    }
    lseek(fd, 0L, 2);
  } else {
    fd = open(name, O_RDONLY, 0);
  }
  if (fd == -1) { /* couldn't access name */
    return NULL;
  }
  fp->fd = fd;
  fp->cnt = 0;
  fp->base = NULL;
  fp->flag = (*mode == 'r') ? _READ : _WRITE;
  return fp;
}

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(MY_FILE *fp)
{
  int bufsize;

  if ((fp->flag & (_READ | _EOF | _ERR)) != _READ) {
    return EOF;
  }

  bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
  if (fp->base == NULL) { /* no buffer yet */
    if ((fp->base = (char *) malloc(bufsize)) == NULL) {
      return EOF; /* can't get buffer */
    }
  }
  fp->ptr = fp->base;
  fp->cnt = read(fp->fd, fp->ptr, bufsize);
  if (--fp->cnt < 0) {
    if (fp->cnt == -1) {
      fp->flag |= _EOF;
    } else {
      fp->flag |= _ERR;
    }
    fp->cnt = 0;
    return EOF;
  }
  return (unsigned char) *fp->ptr++;
}
