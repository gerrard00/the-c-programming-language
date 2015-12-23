#include <stdio.h>
// used for testing remove this, just debugging
#include <string.h>

#define MAXLINE 1000
#define LAST_DISPLAY_COLUMN 15
#define START_AT_TEST 0
#define STOP_AT_TEST 6 /* 5 */
#define DEBUG 0

int my_getline(char line[], int len);
int debug_getline(char s[], int max_len); 
int find_last_whitespace(char s[], int len);
int insert_char(char newChar, char s[], int index, int len); 

int main() 
{
  int len, remaining_length, breakIndex, whitespace_index;
  char line[MAXLINE];
#if STOP_AT_TEST
  while ((len = debug_getline(line, MAXLINE)) > 0) {
    printf("%s\n", line);
#else
  while ((len = my_getline(line, MAXLINE)) > 0) {
#endif

    // ignore the ending newline
    len--;

    breakIndex = 0;

    while ((remaining_length = len - breakIndex) > LAST_DISPLAY_COLUMN) {
      breakIndex += LAST_DISPLAY_COLUMN;
#if DEBUG
      printf("remaining length: %d\n", remaining_length);
      printf("break %c [%d]: \n", line[breakIndex], breakIndex);
#endif
      if (len > LAST_DISPLAY_COLUMN) {
        whitespace_index = 
          find_last_whitespace(line, breakIndex);

        if (whitespace_index > 0) {
#if DEBUG
          printf("last WS charachter: %d\n",
              whitespace_index);
#endif
          line[whitespace_index] = '\n';
          breakIndex = whitespace_index + 1;
#if DEBUG
          printf("%s\n", line);
#endif
        } else {
#if DEBUG
          printf("have to use a hyphen\n");
#endif
          len = insert_char('-', line, breakIndex - 1, len);
          len = insert_char('\n', line, breakIndex, len);
          breakIndex += 2;;
        }
      }
    }
    printf("%s\n", line);
    printf("----------\n");
  }
}

int find_last_whitespace(char s[], int startIndex) 
{
  int i;
  
  i= startIndex;
  while (i > 0 && s[i] != '\n') {
    if (s[i] == ' ' || s[i] == '\t') {
      return i;
    }

    i--;
  }

  return -1;
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

int debug_getline(char s[], int _) 
{
  static int numberOfCalls = START_AT_TEST;
  int len;

  if (numberOfCalls >= STOP_AT_TEST)
    return 0;

  switch(numberOfCalls++) {
    case 0:
      len = strlen("this is a long line\n") + 1;
      memcpy(s, "this is a long line\n", len);
      break;
    case 1:
      len = strlen("this is already too long\n") + 1;
      memcpy(s,    "this is already too long\n", len);
      break;
    case 2:
      len = strlen("this is already too long it really is\n") + 1;
      memcpy(s,    "this is already too long it really is\n", len);
      break;
    case 3:
      len = strlen("123456789012345\n") + 1;
      memcpy(s,    "123456789012345\n", len);
      break;
    case 4:
      len = strlen("0123456789012345\n") + 1;
      memcpy(s,    "0123456789012345\n", len);
      break;
    case 5:
      len = strlen("this is a lesson in speed and effectiveness\n") + 1;
      memcpy(s,    "this is a lesson in speed and effectiveness\n", len);
      break;
    default:
      len = 0;
  }

  return len;
}
