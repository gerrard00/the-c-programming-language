#include <stdio.h>
#include <ctype.h>
#include "getword.h"

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
  int c;
  char *w = word;

  // skip spaces, except newlines
  while (isspace(c = getchar()) && c != '\n') {
    ;
  }

  if (c != EOF) {
    *w++ = c;
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
