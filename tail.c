/* 
Exercise 5-13. Write the program tail, which prints the last n lines 
of its input. By default, n is 10, let us say, but it can be changed 
by an optional argument, so that tail -n prints the last n lines.

The program should behave rationally no matter how unreasonable the 
input or the value of n. Write the program so it makes the
best use of available storage; lines should be stored as in the 
sorting program of Section 5.6, not in a two-dimensionalarray of fixed 
size.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_LINES_TO_PRINT 10
#define MAXLEN 1000
#define MAXLINES 1000

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
int my_getline(char s[], int lim);

#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE]; // Storage for alloc
static char *allocp = allocbuf; // Next free position
char *alloc(int n); // Return pointer to n characters

static char *lineptr[MAXLINES];

int main(int argc, char *argv[]) 
{
  int number_of_lines_to_print, 
      number_of_lines_read,
      offset;

  if (argc == 2) {
    //TODO: it's supposed to be -n, not n
    //TODO: error handling
    number_of_lines_to_print = 0 - atoi(argv[1]);

  } else {
    number_of_lines_to_print = DEFAULT_LINES_TO_PRINT;
  }

  printf("number of lines to print: %d\n", number_of_lines_to_print);

  if((number_of_lines_read = readlines(lineptr, MAXLINES)) >= 0) {
    printf("lines read: %d\n", number_of_lines_read);
    if (number_of_lines_read < number_of_lines_to_print) {
      number_of_lines_to_print = number_of_lines_read;
    }
    offset = number_of_lines_read - number_of_lines_to_print;
    printf("offset: %d\n", offset);
    printf("starting: %s\n", *(lineptr + offset));
    writelines(lineptr + offset, number_of_lines_to_print);
    return 0;
  } else {
    printf("error: input too big for tail\n");
    return -1;
  }

  printf("done!\n");
  return 0;
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
  int len, nlines;
  char *p, line[MAXLEN];

  nlines = 0;
  while ((len = my_getline(line, MAXLEN)) > 0){
    // len + 1 to allocate space for the NULL terminator
    if(nlines >= maxlines || (p = alloc(len + 1)) == NULL) {
      return -1;
    } else {
      strcpy(p, line);
      lineptr[nlines++] = p;
    }
  }

  return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
  for(int i = 0; i < nlines; i++) {
    printf("%s", lineptr[i]);
  }
}

/* my_getline:get line into s, return length */
int my_getline(char *s, int lim)
{
	int c;
  char *original = s;

	while(--lim > 0 && (c=getchar()) != EOF && c != '\n') {
	  *s++ = c;
	}
	if(c =='\n' )
		*s++ = c;
	*s = '\0';
	return s - original;
}

char *alloc(int n) // Return pointer to n characters
{
  if (allocbuf + ALLOCSIZE - allocp >= n) { // it fits
    allocp += n;
    return allocp - n;
  } else
    return 0;
}
