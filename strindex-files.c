#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1000 /* maximum input line length */

int process_file(FILE *file_to_search);
/* call it my_ to avoid name collision with stdio function */
int my_getline(FILE *file, char line[], int max);
int strindex(char source[], char searchfor[]);
int strrindex(char source[], char searchfor[]);

char *pattern; /* pattern to search for */

/* find all lines matching pattern */
int main(int argc, char *argv[])
{
  FILE *current_file;
  switch (argc) {
    case 1:
      break;
    case 2:
      pattern = argv[1];
      process_file(stdin);
      break;
    default:
      pattern = argv[1];

      for(int i = 2; i < argc; i++) {
        printf("File: %s\n-----\n", argv[i]);
        current_file = fopen(argv[i], "r");

        if (current_file == NULL) {
          fprintf(stderr, "Can't open file %s\n", argv[i]);
          exit(-1);
        }
        if(!process_file(current_file)) {
          printf("No matches.\n");
        }
        printf("\n");
      }
      break;
  }
}

int process_file(FILE *file_to_search)
{
  char line[MAXLINE];
  int found =0;
  int found_index;

  /* slight modification, end the loop for an empty line */
  while(my_getline(file_to_search, line, MAXLINE) > 0 && line[0] != '\n') {
    if ((found_index = strindex(line, pattern)) >= 0) {
      printf("%s", line);
      printf("%*s\n", found_index + 1, "^");
      found++;
    }
  }
  return found;
}

/* my_getline:get line into s, return length */
int my_getline(FILE *file, char s[], int lim)
{
  int c, i;

  i=0;
  while(--lim > 0 && (c=getc(file)) != EOF && c != '\n') {
    s[i++] = c;
  }
  if(c =='\n' )
    s[i++] = c;
  s[i]='\0';
  return i;
}

/* strindex:return index of t in s, -1 if none */
int strindex(char s[], char t[])
{
  int i, j, k;

  for (i = 0; s[i] != '\0'; i++) {
    for (j=i, k=0; t[k] != '\0' && s[j] == t[k]; j++, k++)
      ;
    if (k > 0&&t[k] == '\0') {
      return i;
    }
  }
  return-1;
}

/* Exercise 4-1. Write the function strrindex(s, t), which returns the position
of the rightmost occurrence of t in s, or -1if there is none. */
int strrindex(char target[], char pattern[])
{
  int i, j, k;
  int len_target = strlen(target);
  int len_pattern = strlen(pattern);

  for (i = len_target - 1; target[i] != '\0'; i--) {
    for (j = i, k = len_pattern - 1; pattern[k] != '\0' && target[j] == pattern[k]; j--, k--) {
      ;
    }

    if (k < 0) {
      return i - len_pattern + 1;
    }
  }
  return-1;
}


