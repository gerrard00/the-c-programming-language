#include <stdio.h>
// used for testing remove this, just debugging
#include <string.h>

#define MAXLINE 1000
#define TABSTOP 8
#define DEBUG 0
#define TEST 0

//#if DEBUG
//#define SPACE '-'
//#else
#define SPACE ' '
//#endif 

int my_getline(char line[], int len);
int debug_getline(char s[], int max_len); 
int use_tabs(char s[], int len); 
int remove_chars(char s[], int len, int startIndex, int endIndex);

/* use strings of blanks by the minimum number of tabs
 * and blanks to achieve the same spacing */
int main() 
{
  int len, newlen;
  char line[MAXLINE];

#if TEST
  char original_line[MAXLINE];

  while ((len = debug_getline(line, MAXLINE)) > 0) {
    memcpy(original_line, line, len);
#else
  while ((len = my_getline(line, MAXLINE)) > 0) {
#endif
    newlen = use_tabs(line, len); 

#if TEST
    printf("%s", original_line);
#endif
    printf("%s", line);
    printf("\noriginal: %d encoded: %d\n\n", len, newlen);
#if DEBUG
    /* int z; */
    /* for(z = 0; z < newlen; z++) { */
    /*   switch (line[z]) { */
    /*     case'\t': */
    /*       printf("%2d:\\t\n", z); */
    /*       break; */
    /*     case ' ': */
    /*       printf("%2d:_\n", z); */
    /*       break; */
    /*     default: */
    /*       printf("%2d:%c\n", z, line[z]); */
    /*       break; */
    /*   } */
    /* } */
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
      inWord, indexOfWordEnd;
  int numberOfSpaces = 0;
  int newTabIndex;

  i = 0;
  columnIndex = 0;
  inWord = 1;
  indexOfWordEnd = -1;

  while(i < len) {
#if DEBUG
    printf("i: %d ci: %d iw: %d we: %d c: %c\n",
      i, columnIndex, inWord, indexOfWordEnd, s[i]);
#endif
    if (!inWord && columnIndex % TABSTOP == 0) {
      numberOfSpaces = i - indexOfWordEnd - 1;
          // ...check for spaces to replace
#if DEBUG
        printf("#sp: %d\n", numberOfSpaces);
#endif
        if(numberOfSpaces > 1) {
          newTabIndex = indexOfWordEnd + 1;
#if DEBUG
          printf("need some tab action: startIndex %d endIndex: %d\n",
              newTabIndex, i - 1);
#endif
          s[newTabIndex] = '\t';
          len = remove_chars(s, len, newTabIndex + 1, i - 1);
          indexOfWordEnd = newTabIndex;
          i = newTabIndex + 1;
#if DEBUG
          printf("%s\n", s);
          printf("reset i: %d\n", i);
#endif
        } else {
          //we can't go back over a tab stop
          indexOfWordEnd = i;
        }
    }
    
    if(s[i] == SPACE) {
      if (inWord) {
        indexOfWordEnd = i - 1;
        inWord = 0;
      }
    } else {
      if (!inWord) {
        inWord = 1;
      }
    }
  
    i++;
    columnIndex++;
  }

/*
      if (i - indexOfWordEnd > 1 
          && (columnIndex % TABSTOP) == 0) {
#if DEBUG
        printf("_t:%d:%d\n", i, columnIndex);
#endif 
        s[indexOfWordEnd + 1] = '\t';
        len = remove_chars(s, len, indexOfWordEnd + 2, i);
        i = indexOfWordEnd + 1;
        indexOfWordStart = i;
#if DEBUG
        printf("i is now %d\n", i);
        printf("columnIndex is now %d\n", columnIndex);
        printf("len is now %d\n", len);
#endif 
      }
      else {
#if DEBUG
        printf("_:%d:%d\n", i, columnIndex);
#endif 
        indexOfWordStart = -1;
      }
    //TOO:magic number
    } else if (indexOfWordStart == -1) {
#if DEBUG
      printf("%c:%d:%d<\n", s[i], i, columnIndex);
#endif 
      indexOfWordStart = i;
    } else {
#if DEBUG
      printf("%c:%d:%d\n", s[i], i, columnIndex);
#endif 
    }
    i++;
    columnIndex++;
  }
printf("column: %d\n", columnIndex);
  return len;
  */
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

int debug_getline(char s[], int _) 
{
  static int numberOfCalls = 0;
  int len;

  switch(numberOfCalls++) {
    case 0:
      len = strlen("this is                   sparta\n") + 1;
      memcpy(s,    "this is                   sparta\n", len);
      break;
    case 1:
      len = strlen("a                   sparta\n") + 1;
      memcpy(s,    "a                   sparta\n", len);
      break;
    case 2:
      len = strlen("this         is                   sparta\n") + 1;
      memcpy(s,    "this         is                   sparta\n", len);
      break;
    case 3:
      len = strlen("this              is   a   thing      ok  y\n") + 1;
      memcpy(s,    "this              is   a   thing      ok  y\n", len);
      break;
    case 4:
      len = strlen("this thingosaurus rex is a lifestyle for me.\n") + 1;
      memcpy(s,    "this thingosaurus rex is a lifestyle for me.\n", len);
      break;
    case 5:
      len = strlen("0123456789012345  gerrard     lindsay\n") + 1;
      memcpy(s,    "0123456789012345  gerrard     lindsay\n", len);
      break;
    case 6:
      len = strlen("this    e               slfdk\n") + 1;
      memcpy(s,    "this    e               slfdk\n", len);
    case 7:
      len = strlen("01234567 90123   7\n") + 1;
      memcpy(s,    "01234567 90123   7\n", len);
      break;
      break;
    default:
      len = 0;
  }

  return len;
}
