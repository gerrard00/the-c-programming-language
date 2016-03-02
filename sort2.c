#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLEN 1000
#define MAXLINES 5000
char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines,
    bool (*iter)(int, int *));

/* have to call it my_qsort because there is a qsort
 * in the stdlib. probabaly wasn't there in c99 era */
void my_qsort(void *lineptr[], int left, int right,
    int (*comp)(void *, void *));

int numcmp(const char *, const char*);

/*
Exercise 5-14. Modify the sort program to handle a -r flag,
which indicates sorting in reverse (decreasing) order. Be sure
that -r works with -n.
*/
/* don't really need an iterator, just having fun */
bool iterate(int number_of_items, int *next);
bool iterate_rev(int number_of_items, int *next);

/*
Exercise 5-15. Add the option -f to fold upper and lowercase together,
so that case distinctions are not made during sorting; for example,
a and A compare equal.
*/
int strcmp_ignore_case(char *s1, char *s2);

/*
Exercise 5-16. Add the -d ("directory order") option, which makes
comparisons only on letters, numbers and blanks. Make sure it works in
conjunction with- f.
*/
/* support nested comparers (e.g. strcmp_directory) that modify the
 * input string before calling inner_comparer to do the actual
 * comparison
*/
static char modified1[MAXLEN], modified2[MAXLEN];
static int (*inner_comparer)(void *, void *);
int strcmp_directory(char *s1, char *s2);

/*
Exercise 5-17. Add a field-handling capability, so sorting may be done 
on fields within lines, each field sorted according to an independent 
set of options. (The index for this book was sorted with -df for the 
index category and -n for the page numbers.
*/
//TODO: support a static array of comparers, instead of the current local scalar var in main
/* sort input lines */
int main(int argc, char *argv[])
{
  int nlines; /* number of input lines */
  bool numeric, reverse_order, ignore_case, directory_order;
  int (*comparer)(void*, void*) = NULL;
  char current_argument_char;

  numeric = reverse_order = ignore_case = directory_order = false;

  for(int arg_index = 1; arg_index < argc; arg_index++) {
    char *current_argument = argv[arg_index];
    if (*current_argument != '-') {
      printf("Unknown option %s\n", current_argument);
      return 4;
    }

    // skip the leading dash
    current_argument++;

    while((current_argument_char = *current_argument++) != '\0') {
      switch(current_argument_char) {
        case 'n':
          numeric = true;
          break;
        case 'r':
          reverse_order = true;
          break;
        case 'f':
          ignore_case = true;
          break;
        case 'd':
          directory_order = true;
          break;
        default:
          printf("Unknown option.\n");
          return 5;
      }
    }

    if (numeric && ignore_case) {
      printf("You cannot specify both -n and -f\n");
      return 2;
    }

    if (numeric && directory_order) {
      printf("You cannot specify both -n and -d\n");
      return 3;
    }

    // determine primary comparer
    if (numeric) {
      comparer = (int (*)(void*, void*))numcmp;
    } else if (ignore_case) {
      comparer = (int (*)(void*, void*))strcmp_ignore_case;
    }

    //use default comparer if no args were specified 
    if (comparer == NULL) {
      comparer = (int (*)(void*, void*))strcmp;
    }

    // see if we need a wrapper comparer
    if (directory_order) {
      inner_comparer = comparer;
      comparer = (int (*)(void*, void*))strcmp_directory;
    }

    argv[arg_index]++;
  }


  // if we still don't have a comparer (i.e. no args)
  // use default comparer if no args were specified 
  if (comparer == NULL) {
    comparer = (int (*)(void*, void*))strcmp;
  }

  if((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    my_qsort((void*)lineptr, 0, nlines-1, comparer);
    writelines(lineptr, nlines, (reverse_order ? iterate_rev : iterate));
    return 0;
  } else {
    printf("error: input too big to sort\n");
    return 1;
  }
}

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
void writelines(char *lineptr[], int nlines, bool (*iter)(int, int *))
{
  int index_to_write;

  while(iter(nlines, &index_to_write)) {
    printf("-> %s\n", lineptr[index_to_write]);
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

/* my_qsort: sort v[left]...v[right] into increasing order */
void my_qsort(void *v[], int left, int right,
    int (*comp)(void *, void *))
{
  int i, last;
  void swap(void *v[], int i, int j);

  if (left >= right) { /* do nothing if array contains */
    return;            /* fewer than two elements */
  }
  swap(v, left, (left + right)/2);
  last = left;
  for(i = left+1; i <= right; i++) {
    if((*comp)(v[i], v[left]) < 0) {
      swap(v, ++last, i);
    }
  }
  swap(v, left, last);
  my_qsort(v, left, last - 1, comp);
  my_qsort(v, last+1, right, comp);
}

/* swap; interchange v[i] and v[j] */
void swap(void *v[], int i, int j)
{
  void *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(const char *s1, const char *s2)
{
  double v1, v2;

  v1 = atof(s1);
  v2 = atof(s2);

  if (v1 < v2) {
    return -1;
  } else if (v1 > v2) {
    return 1;
  } else {
    return 0;
  }
}

void copy_directory_chars(char *from, char *to)
{
  while(*from != '\0') {
    // filter anything but letters, numbers and blanks
    if (isdigit(*from)
        || *from == ' '
        || (*from >=  'a' && *from <= 'z')
        || (*from >=  'A' && *from <= 'Z')) {

      *to++ = *from;
    }

    from++;
  }
}

int strcmp_directory(char *s1, char *s2)
{
  char *s1mod = modified1;
  char *s2mod = modified2;

  copy_directory_chars(s1, s1mod);
  copy_directory_chars(s2, s2mod);

  return (*inner_comparer)(modified1, modified2);
}

int strcmp_ignore_case(char *s1, char *s2)
{
  char c1, c2;

  while(*s1 != '\0' && *s2 != '\0'
      && (c1 = tolower(*s1++)) == (c2 = tolower(*s2++))) {
    ;
  }
  return c1 - c2;
}

static int current_index = 0;
static int current_rev_index = 0;

void clear_iterate()
{
  current_index = 0;
}

void clear_iterate_rev()
{
  current_rev_index = 0;
}

bool iterate(int number_of_items, int *next)
{
  *next = current_index++;
  return *next < number_of_items;
}

bool iterate_rev(int number_of_items, int *next)
{
  *next = number_of_items - current_index++ - 1;
  return *next >= 0;
}
