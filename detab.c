#include <stdio.h>

#define MAXLINE 1000
#define TABSTOP 8

int my_getline(char line[], int len);
int replace_tabs(char s[], int len); 
int insert_char(char newChar, char s[], int index, int len); 

/* replace strings of blanks by the minimum number of tabs
 * and blanks to achieve the same spacing */
int main() 
{
  int len, newlen;
  char line[MAXLINE];

  while ((len = my_getline(line, MAXLINE)) > 0) {
    newlen = replace_tabs(line, len);
    printf("%s\n", line);
    printf("original: %d encoded: %d\n\n", len, newlen);
  }
}

/* my_getline: read a line into s, return length */
int my_getline(char s[], int len) 
{
  int c, i;

  for(i=0; (c=getchar())!=EOF && c!='\n'; ++i) {
    if(i<len-1) {
      s[i] = c;
    }
  }
  if(c == '\n') {
    s[i] = c;
    ++i;
  }

  // do we need an ellipse?
  if (i > len - 1) {
    s[len - 4] = '.';
    s[len - 3] = '.';
    s[len - 2] = '.';
    s[len - 1] = '\0';
  } else {
    s[i] = '\0';
  }
  return i;
}

int replace_tabs(char s[], int len) 
{
  int i;

  i = 0;
  while(i < len && len < MAXLINE) {
    if(s[i] == '\t') {
      s[i] = ' ';
      while(++i % TABSTOP != 0 && len < MAXLINE) {
        len = insert_char(' ', s, i, len);
      }
      /* printf("--------------\n"); */
      /* printf("%s\n", s); */
    } else {
      i++;
    }
  }
  return len;
}

int insert_char(char newChar, char s[], int index, int len) 
{
  int i;
  char last, next;
  last = newChar;

  for(i = index; i <= len; i++) {
    next = s[i];
    s[i] = last;
    last = next;
  }

  s[++len] = '\0';

  return len;
}
