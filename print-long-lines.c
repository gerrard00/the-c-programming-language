#include <stdio.h>

#define MAXLINE 1000 /* maximum input line size */
#define TARGET_LENGTH 5 /* maximum input line size */

int my_getline(char line[], int maxline);

/* print lines longer tan TARGET_LENGTH */
int main() 
{
  int len;    /* current line length */
  int max;    /* maximum length seen so far */
  char line[MAXLINE];   /* current input line */

  max = 0;
  while((len = my_getline(line, MAXLINE)) > 0) {
    if (len > TARGET_LENGTH) {
      printf("%s", line);
    }
  }

  printf("\n");

  return 0;
}

/* my_getline: read a line into s, return length */
int my_getline(char s[], int lim) 
{
  int c, i;

  for(i=0; (c=getchar())!=EOF && c!='\n'; ++i) {
    if(i<lim-1) {
      s[i] = c;
    }
  }
  if(c == '\n') {
    s[i] = c;
    ++i;
  }

  // do we need an ellipse?
  if (i > lim - 1) {
    s[lim - 4] = '.';
    s[lim - 3] = '.';
    s[lim - 2] = '.';
    s[lim - 1] = '\0';
  } else {
    s[i] = '\0';
  }
  return i;
}
