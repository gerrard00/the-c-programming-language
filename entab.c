#include <stdio.h>
// TODO:remove this, just debugging
#include <string.h>

#define MAXLINE 1000
#define TABSTOP 8
#define DEBUG 0

int my_getline(char line[], int len);
int use_tabs(char s[], int len); 
int remove_chars(char s[], int len, int startIndex, int endIndex);

/* use strings of blanks by the minimum number of tabs
 * and blanks to achieve the same spacing */
int main() 
{
  int len, newlen;
  char line[MAXLINE];

  while ((len = my_getline(line, MAXLINE)) > 0) {
    newlen = use_tabs(line, len); 
    printf("%s", line);
    printf("original: %d encoded: %d\n\n", len, newlen);
#if DEBUG
    int z;
    for(z = 0; z < newlen; z++) {
      switch (line[z]) {
        case'\t':
          printf("%2d:\\t\n", z);
          break;
        case ' ':
          printf("%2d:_\n", z);
          break;
        default:
          printf("%2d:%c\n", z, line[z]);
          break;
      }
    }
#endif    
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

int use_tabs(char s[], int len) 
{
  int i, columnIndex, 
      indexOfWordStart, indexOfWordEnd;

  i = columnIndex = 0;
  indexOfWordStart = -1;
  while(i < len) {
    if(s[i] == ' ') {
      if (indexOfWordStart != -1) {
        indexOfWordEnd = i - 1;
      }

      if (i - indexOfWordEnd > 1 
          && ((columnIndex + 1) % TABSTOP) == 0) {
#if DEBUG
        printf("_t:%d\n", i);
#endif 
        s[indexOfWordEnd + 1] = '\t';
        len = remove_chars(s, len, indexOfWordEnd + 2, i);
        i = indexOfWordEnd + 1;
        indexOfWordStart = i;
#if DEBUG
        printf("i is now %d\n", i);
        printf("len is now %d\n", len);
#endif 
      }
      else {
#if DEBUG
        printf("_:%d\n", i);
#endif 
        indexOfWordStart = -1;
      }
    //TOO:magic number
    } else if (indexOfWordStart == -1) {
#if DEBUG
      printf("%c:%d<\n", s[i], i);
#endif 
      indexOfWordStart = i;
    } else {
#if DEBUG
      printf("%c:%d\n", s[i], i);
#endif 
    }
    i++;
    columnIndex++;
  }

  return len;
}

int remove_chars(char s[], int len, int startIndex, int endIndex) 
{
  int newlen, i;

  newlen = startIndex;
  i = endIndex + 1;

  while(i < len) {
    s[newlen] = s[i];
    ++newlen;
    ++i;
  }
  s[newlen] = '\0';
  return newlen;
}
