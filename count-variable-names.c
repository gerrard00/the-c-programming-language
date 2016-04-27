#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "binary-tree.h"

#define MAXWORD 100

int getword(char *, int);

int main() 
{
  char word[MAXWORD];
  tnode *root = talloc();

  while (getword(word, MAXWORD) != EOF) {
    if (root->word == NULL) {
      root = addtree(NULL, word);
    } else {
      addtree(root, word); 
    }

    treeprint(root);
    printf("**********\n");
  }

  printf("\ndone!\n");
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
