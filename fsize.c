#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>

void fsize(char *);
void dirwalk(char *, void (*fcn)(char *));
void printlocaltime(time_t input);


int main(int argc, char **argv)
{
  printf("starting\n");
  if(argc == 1) {   /* default: current directory */
    fsize(".");
  } else {
    printf("bang: %d\n", argc);
    while (--argc > 0) {
      fsize(*++argv);
    }
  }

  return 0;
}

/* fsize: print size of file "name" */
void fsize(char *name)
{
  struct stat stbuf;

  if (stat(name, &stbuf) == -1) {
    fprintf(stderr, "fsize: can't access %s\n", name);
    return;
  }

  if (S_ISDIR(stbuf.st_mode)) {
    dirwalk(name, fsize);
  }
  printf("%8ld %s\n", stbuf.st_size, name);
  printlocaltime(stbuf.st_mtime);
}

#define MAX_PATH 1024

/* dirwalk: apply fcn to all files in dir */
void dirwalk(char *dir, void (*fcn)(char *))
{
  printf("walk: %s\n", dir);
  char name[MAX_PATH];
  struct dirent *dp;
  DIR *dfd;

  if ((dfd = opendir(dir)) == NULL) {
    fprintf(stderr, "dirwalk: can't open %s\n", dir);
    return;
  }
  while ((dp = readdir(dfd)) != NULL) {
    if (strcmp(dp->d_name, ".") == 0
        || strcmp(dp->d_name, "..") == 0) {

      continue;
    }
    if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name)) {
      fprintf(stderr, "dirwalk: name %s/%s too long\n",
          dir, dp->d_name);
    } else {
      sprintf(name, "%s/%s", dir, dp->d_name);
      (*fcn)(name);
    }
  }
  closedir(dfd);
}

void printlocaltime(time_t input)
{
  struct tm *time = localtime(&input);
  printf("\tModified: %s\n", asctime(time));
}

