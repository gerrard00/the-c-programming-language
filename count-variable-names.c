#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "binary-tree.h"

#define MAXWORD 100

int getword(char *, int);
void treeprint_groups(tnode *, int);
static tnode *root = NULL;

//TODO: doesn't actually just read variable names, it 
// grabs any word that starts with a letter or underscore.
// I'm going to punt on that.
int main(int argc, char *argv[]) 
{
  unsigned int chars_to_compare;
  char word[MAXWORD];

  // accept the number of chars to compare as
  // a command line argument
  switch(argc) {
    case 1:
      chars_to_compare = MAXWORD;
      break;
    case 2:
      chars_to_compare = (unsigned int)atoi(argv[1]);
      break;
    default:
      printf("Must be run with no arguments,"
        " or with a single argument indicating"
        " comparison length.");
      return -1;
  }

  printf("\nComparing %u characters.\n", chars_to_compare);

  while (getword(word, MAXWORD) != EOF) {
    // ignore things that can't be variable names
    // variable names have to start with a letter
    // or an underscore.
    if (!isalpha(*word) && *word != '_') {
      continue;
    }
    if (root == NULL) {
      root = addtree(NULL, word);
    } else {
      addtree(root, word); 
    }
  }

  printf("\n");
  treeprint_groups(root, chars_to_compare);
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

static char laststembuf[MAXWORD]; // Storage for alloc
static char *laststemp = laststembuf; // Next free position
static unsigned int words_in_group;
static bool found_leftmost = false;

/* treeprint: in-order print of tree p */
void treeprint_groups(tnode *p, int num_chars)
{
  if (p != NULL) {
    if (!found_leftmost && p->left == NULL) {
      found_leftmost = true;
    }

    treeprint_groups(p->left, num_chars);
    if(found_leftmost && strncmp(laststemp, p->word, num_chars) != 0) {
      // end of previous group
      if (words_in_group > 0) {
        printf("\n\tNumber of words: %d\n", words_in_group);
      }
      strcpy(laststemp, p->word);
      printf("\nGroup: \"%s\"\n\n", laststemp);
      words_in_group = 0;
    }
    printf("%4d %s\n", p->count, p->word);
    words_in_group++;
    treeprint_groups(p->right, num_chars);

    // we are done processing the tree
    if (p == root) {
      // hack to print the last group
      printf("\n\tNumber of words: %d\n", words_in_group);
    }
  }
}
