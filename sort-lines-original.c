#include <stdio.h>
#include <string.h>

#define MAXLINES 5000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);

/* sort input lines */
int main()
{
  printf("Enter lines, then an empty line.\n");

  int nlines; /* number of input lines */

  if((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    qsort(lineptr, 0, nlines-1);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("error: input too big to sort\n");
    return 1;
  }
}

#define MAXLEN 1000
int my_getline(char *, int);
char *alloc(int);

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
    printf("-> %s\n", lineptr[i]);
  }
}

/* my_getline: read a line into s, return length */
/* or return EOF if EOF received */
/* my_getline:get line into s, return length */
int my_getline(char *s, int lim)
{
  char *s_mod = s;
	char c;

	while(--lim > 0 && (c=getchar()) != EOF && c != '\n') {
    *s_mod++ = c;
	}

	*s_mod = '\0';

	return (s_mod - s);
}

#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE]; // Storeage for alloc
static char *allocp = allocbuf; // Next free position

char *alloc(int n) // Return pointer to n characters
{
  if (allocbuf + ALLOCSIZE - allocp >= n) { // it fits
    allocp += n;
    return allocp - n;
  } else
    return 0;
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
  int i, last;
  void swap(char *v[], int i, int j);

  if (left >= right) { /* do nothing if array contains */
    return;            /* fewer than two elements */
  }
  swap(v, left, (left + right)/2);
  last = left;
  for(i = left+1; i <= right; i++) {
    if(strcmp(v[i], v[left]) < 0) {
      swap(v, ++last, i);
    }
  }
  swap(v, left, last);
  qsort(v, left, last - 1);
  qsort(v, last+1, right);
}

/* swap; interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
  char *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}
