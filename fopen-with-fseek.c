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
typedef struct iobuf {
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
#undef putc
#define putc(x,p) (--(p)->cnt >= 0 \
    ? *(p)->ptr++ = (x) : _flushbuf((x),p))

MY_FILE *my_fopen(char *name, char *mode);
int _fillbuf(MY_FILE *fp);
int _flushbuf(int c, MY_FILE *fp);
int my_fflush(MY_FILE *fp);
int my_fclose(MY_FILE *fp);
int my_fseek(MY_FILE*fp, long offset, int origin);


int main(int argc, char *argv[])
{
  MY_FILE *input_file;
  MY_FILE *output_file;
  int skip_start, skip_count;
  int skip_index = 0;
  int skip_origin = 0;
  char c;

  if (argc < 6) {
    // feels dirty using fprintf to stderr
    return -1;
  }

  input_file = my_fopen(argv[1], "r");
  output_file = my_fopen(argv[2], "w");
  skip_start = atoi(argv[3]);
  skip_count = atoi(argv[4]);
  skip_origin = atoi(argv[5]);

  /* putc('!', output_file); */
  while((c = getc(input_file)) != EOF) {
    putc(c, output_file);

    if (skip_index++ == skip_start) {
      my_fseek(input_file, skip_count, skip_origin);
    }
  }

  my_fclose(input_file);
  my_fclose(output_file);
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
      fp->flag.is_err = 1;
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

/* _flushbuf: flush dat buffer */
int _flushbuf(int c, MY_FILE *fp)
{
  int bufsize;

  if (fp->flag.is_eof) {
    return EOF;
  }

  bufsize = (fp->flag.is_unbuffered) ? 1 : BUFSIZ;
  if (fp->base == NULL) { /* no buffer yet */
    if ((fp->base = (char *) malloc(bufsize)) == NULL) {
      printf("can't create buffer\n");
      return EOF; /* can't get buffer */
    }

    /* just write the char to the buffer, */
    /* don't flush to real stream */
    fp->ptr = fp->base;
    *(fp)->ptr++ = c;
    /* dec the cnt by 1 for c */
    fp->cnt = bufsize - 1;

    return c;
  }

  /* it's not the first call for this fp */
  if (c != EOF) {
    *(fp)->ptr = c;
  }

  write(fp->fd, fp->base, bufsize - fp->cnt);

  fp->ptr = fp->base;
  fp->cnt = bufsize;

  fp->flag.is_eof = (c == EOF);

  /* TODO: error handling */

  return c;
}

int my_fflush(MY_FILE *fp)
{
  return _flushbuf(EOF, fp);
}

int my_fclose(MY_FILE *fp)
{
  if (fp->flag.is_write &&
      !fp->flag.is_unbuffered) {
    my_fflush(fp);
    //TODO: error handling
  }

  return close(fp->fd);
}

int my_fseek(MY_FILE*fp, long offset, int whence)
{
/* TODO: could optimize and not re-read if the target index is in the buffer, but I'm lazy. */
  int actual_offset = offset;

  if (whence == SEEK_CUR) {
    actual_offset -= fp->cnt;
  }

  off_t result = lseek(fp->fd, actual_offset, whence);

  // reset the buffer
  fp->cnt = -1;

  return (result == -1)
    ? result
    : 0;
}
