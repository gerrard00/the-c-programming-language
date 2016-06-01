#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "table-lookup.h"

#define MAXWORDSIZE 100

int getword(char *word, int lim);

int main()
{
  char word[MAXWORDSIZE];
  char previous_word[MAXWORDSIZE];
  bool in_macro_definition = false;
  bool got_name = false;
  bool in_macro_undefinition = false;

  while(getword(word, MAXWORDSIZE) != EOF) {
    if (in_macro_definition) {
      in_macro_definition = false;
      got_name = true;
    } else if (got_name) {
      install(previous_word, word);
      got_name = false;
    } else if (in_macro_undefinition) {
      undef(word);
      in_macro_undefinition = false;
    } else if (strcmp("#define", word) == 0) {
      in_macro_definition = true;
    } else if (strcmp("#undef", word) == 0) {
      in_macro_undefinition = true;
    }

    strcpy(previous_word, word);
  }

  printtable();
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
  int c;
  char *w = word;

  // skip spaces, except newlines
  while (isspace(c = getchar()) && c != '\n') {
    ;
  }

  if (c == EOF) {
    return EOF;
  }

  *w++ = c;

 /* this doesn't apply in our case, since we want #define */
 /* if (!isalpha(c)) { */
 /*    *w = '\0'; */
 /*    return c; */
 /*  } */

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
