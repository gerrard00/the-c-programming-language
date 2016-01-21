
#include <stdio.h>
#include <string.h>

#define MAXLINE 1000 /* maximum input line length */

/* call it my_ to avoid name collision with stdio function */
int my_getline(char line[], int max);
int strindex(char source[], char searchfor[]);
int strrindex(char source[], char searchfor[]);

char pattern[] = "ould"; /* pattern to search for */

/* find all lines matching pattern */
int main( )
{
	char line[MAXLINE];
	int found =0;
  int found_index;

  /* slight modification, end the loop for an empty line */
	while(my_getline(line, MAXLINE) > 0 && line[0] != '\n') {
		if ((found_index = strrindex(line, pattern)) >= 0) {
			printf("%d > %s",found_index, line);
			found++;
 		}
	}
	return found;
}

/* my_getline:get line into s, return length */
int my_getline(char s[], int lim)
{
	int c, i;

	i=0;
	while(--lim > 0 && (c=getchar()) != EOF && c != '\n') {
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


