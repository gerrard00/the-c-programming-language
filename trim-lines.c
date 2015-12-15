#include <stdio.h>

#define MAXLINE 1000 /* maximum input line size */

int my_getline(char line[], int maxline);
int trim_line(char line[], int length);

/* print lines longer tan TARGET_LENGTH */
int main() 
{
  int len, trimmed_len;    /* current line length */
  char line[MAXLINE];   /* current input line */

  while((len = my_getline(line, MAXLINE)) != EOF) {
    trimmed_len =trim_line(line, len);
    if (trimmed_len > 0) {
      //printf("length:%d trim:%d \n", len, trimmed_len);
      printf("\"%s\"\n", line);
    }
  }

  printf("\n");

  return 0;
}

/* my_getline: read a line into s, return length */
/* or return EOF if EOF received */
int my_getline(char s[], int lim) 
{
  int c, i;

  for(i=0; (c=getchar())!=EOF && c!='\n'; ++i) {
    if(i<lim-1) {
      s[i] = c;
    }
  }

  if(c == EOF) {
    return EOF;
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

int trim_line(char line[], int length)
{
  int i;

  for(i = length - 1; i >=0; i--) {
    if (line[i] != ' '
        && line[i] != '\t') {
      break;
    }
  }

  i++;

  line[i] = '\0';

  return i;
}
