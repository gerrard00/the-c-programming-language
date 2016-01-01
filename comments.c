#include <stdio.h>
#include <unistd.h>

/*
 * stupid comments for testing strip-comments^^
 * this one goes on for a while^^
 * lots of lines here^^
 */
int main() 
{
  int i = 0;

  while(i < 10) {
    /* this is a multi-line style comment on a single line */
    printf("%d-", getpid());
    // we have to flush, since our printf has no newline
    // let's throw an extra comment here
    fflush(stdout);
    // this is what slows it down
    sleep(1);

    printf("test\n"); // this line has an empty live above it
    /* //this is supported, but it is dumb */
    /* printf("this is dumb\n"); /1* multi starting in middle */
/* this is more comments */
/* and more */
/* and now it ends */ 
    /* *1/printf("really dumb\n"); */
    i++;
  }

  printf("this is a quoted string /* so this is not a comment */.\n");
}
