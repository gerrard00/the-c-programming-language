#include <stdio.h>

#define MAXLINE 1000 /* maximum input line size */

int my_getline(char line[], int maxline);
void reverse(char s[], int length);

/* print lines longer tan TARGET_LENGTH */
int main() 
{
  int len;    /* current line length */
  char line[MAXLINE];   /* current input line */

  while((len = my_getline(line, MAXLINE)) != EOF) {
    reverse(line, len);
    printf("%s\n", line);
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

void reverse(char s[], int length)
{
  char temp;
  int middle_index, i, target_index;
  
  middle_index = length/2;

  for(i = 0; i < middle_index; i++) {
    target_index = length - i - 1;
    temp = s[i];
    s[i] = s[target_index];
    s[target_index] = temp;
  }
}

