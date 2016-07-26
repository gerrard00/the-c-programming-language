#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define PERMS 0666 /* RW for owner, group, others */

/* there's no OPEN_MAX on linux */
#define OPEN_MAX FOPEN_MAX

/* can't find these macros anywhere */
/* copied this from book */
typedef struct {
  unsigned int is_read : 1;     /* file open for reading */
  unsigned int is_write : 1;    /* file open for writing */
  unsigned int is_unbuffered : 1;     /* file is unbuffered */
  unsigned int is_eof : 1;      /* EOF has occurred on this file */
  unsigned int is_err : 1;      /* error occurred on this file */
} FLAGS;

/* real FILE is undocumented, use this from k&r */
typedef struct iobuf{
  int cnt; /* characters left */
  char *ptr; /* next character position */
  char *base; /* location of buffer */
  FLAGS flag;/*mode of file access*/
  int fd;/*file descriptor*/
} MY_FILE;

MY_FILE _iob[OPEN_MAX] = { /* stdin, stdout, stderr */
  { 0, (char *) 0, (char *) 0, .flag.is_read = 1, .fd = 0 },
  { 0, (char *) 0, (char *) 0, .flag.is_write = 1, .fd = 1 },
  { 0, (char *) 0, (char *) 0,
    .flag.is_write = 1, .flag.is_unbuffered = 1, .fd = 2 }
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
    if (fp->flag.is_read == 0 && fp->flag.is_write == 0) {
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
  switch (*mode) {
    case 'r':
      fp->flag.is_read = 1;
      break;
    case 'w':
      fp->flag.is_write = 1;
    break;
  }
  return fp;
}

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(MY_FILE *fp)
{
  int bufsize;

  if (fp->flag.is_eof) {
    return EOF;
  }

  bufsize = (fp->flag.is_unbuffered) ? 1 : BUFSIZ;
  if (fp->base == NULL) { /* no buffer yet */
    if ((fp->base = (char *) malloc(bufsize)) == NULL) {
      return EOF; /* can't get buffer */
    }
  }
  fp->ptr = fp->base;
  fp->cnt = read(fp->fd, fp->ptr, bufsize);
  if (--fp->cnt < 0) {
    if (fp->cnt == -1) {
      fp->flag.is_eof = 1;
    } else {
      fp->flag.is_err = 1;
    }
    fp->cnt = 0;
    return EOF;
  }
  return (unsigned char) *fp->ptr++;
}
