#include <stdio.h>
#include <ctype.h>
#include <string.h>

struct key {
  char *word;
  int count;
};

struct key keytab[] = {
  { "auto",0 },
  { "break", 0},
  { "case", 0},
  { "char", 0},
  { "const", 0},
  { "continue", 0},
  { "default", 0},
  { "int", 0},
  /* ... */
  { "unsigned", 0},
  { "void", 0},
  { "volatile", 0},
  { "while", 0}
};

#define NKEYS (sizeof keytab / sizeof keytab[0])

#define MAXWORD 100

int getword(char*, int);
int binsearch(char *, struct key *, int);

/* too lazy to get old code for getch and ungetc,
 * instead use built in getchar and ungetc */

/* count C keywords */
int main()
{
  unsigned int n;
  int index_of;
  char word[MAXWORD];

  while (getword(word, MAXWORD) != EOF) {
    if (isalpha(word[0])) {
      if ((index_of = binsearch(word, keytab, NKEYS)) >= 0) {
        keytab[index_of].count++;
      }
    }
  }
  for(n = 0; n < NKEYS; n++) {
    if (keytab[n].count > 0) {
      printf("%4d %s\n",
          keytab[n].count, keytab[n].word);
    }
  }
  return 0;
}

/* binsearch: find word in tab0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n)
{
  int cond;
  int low, high, mid;

  low = 0;
  high = n - 1;
  while(low <= high) {
    mid = (low+high) / 2;
    if ((cond = strcmp(word, tab[mid].word)) < 0) {
      high = mid -1;
    } else if (cond > 0) {
      low = mid + 1;
    } else {
      return mid;
    }
  }
  return -1;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
  int c;
  char *w = word;

  while (isspace(c = getchar())) {
    ;
  }

  if (c != EOF) {
    *w++ = c;
  }

  // If the char is a quote, assume we are starting a string
  // constant. We need to skip chars until we reach the end
  // of the string constant.
  if (c == '"') {
    while((c = getchar()) != '"' && c != EOF && c!= '\n') {
      ;
    }

    // if the current character isn't a closing quote, we have
    // an unterminated string constant.
    if (c != '"') {
      printf("Unterminated string constant.\n");
      return -1;
    }

    *w = '\0';
    return c;
  }

  // if we have "/*" assume that we are starting a comment.
  if (c == '/') {
    // look for an asterisk to see if we are starting a comment
    if ((c = getchar()) == '*') {
      // now we have to find the end of the comment
      while((c = getchar()) != EOF) {
        // if the current char is an asterisk, we may have found
        // the end of the comment
        if (c == '*') {
          // are we at the end?
          if ((c = getchar()) == '/') {
            // we found the end of our comment, break out of the loop
            break;
          } else {
            ungetc(c, stdin);
          }
        }
      }

      if (c != '/') {
        printf("Unterminated c style comment.\n");
        return -1;
      }

      *w = '\0';
      return c;
    } else {
      // not a comment
      ungetc(c, stdin);
    }
  }

  // if we see a # it's a preprocessor directive
  if (c == '#') {
    // now we have to find the end of the directive
    while((c = getchar()) != EOF) {
      // if the current char is a line continuation ('/'), 
      // and the next char is a newline, we need to swallow
      // that newline since the directive continues.
      if (c == '/') {
        //is the next char a newline?
        if ((c = getchar()) != '\n') {
          // if not, unswallow the char, it's not a line
          // continuation
          ungetc(c, stdin);
        }
      } else if (c == '\n') {
        // we've found the end of our directive
        break;
      }
    }

    if (c == EOF) {
      printf("Unterminated directive.\n");
      return -1;
    }

    *w = '\0';
    return c;
  }

  if (!isalpha(c)) {
    *w = '\0';
    return c;
  }

  for( ; --lim > 0; w++) {
    // a word ends when we have a char that's not a letter,
    // number, or underscore
    if (!isalnum(*w = getchar()) && *w != '_') {
      ungetc(*w, stdin);
      break;
    }
  }
  *w = '\0';
  return word[0];
}
