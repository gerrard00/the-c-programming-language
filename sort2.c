#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLEN 1000
#define MAXLINES 5000
#define MAXARGS 20

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

/* have to call it my_qsort because there is a qsort
 * in the stdlib. probabaly wasn't there in c99 era */
void my_qsort(void *lineptr[], int left, int right,
    int (*comparer[])(void *, void *),
    bool (*orderer[])(int),
    int (*wrapper_comparer[])(void *, void *, int (*comparer)(void *, void *)));

int numcmp(const char *, const char*);

/*
Exercise 5-14. Modify the sort program to handle a -r flag,
which indicates sorting in reverse (decreasing) order. Be sure
that -r works with -n.
*/
// sort order forward
bool order_forward(int input);
// sort order reverse
bool order_reverse(int input);

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
/* support nested comparers (e.g. directory) that modify the
 * input string before calling inner_comparer to do the actual
 * comparison
*/

int wrapper_strcmp_directory(void *s1, void *s2,
    int (*inner_comparer)(void *, void *));

int wrapper_strcmp_passthrough(void *s1, void *s2,
    int (*inner_comparer)(void *, void *));

int get_comparers_and_orderer(char *argument,
  int (**comparer)(void *, void *),
  bool (**order)(int),
  int (**wrapper_comparer)(void *, void *,int (*comparer)(void *, void *)));

/*
Exercise 5-17. Add a field-handling capability, so sorting may be done
on fields within lines, each field sorted according to an independent
set of options. (The index for this book was sorted with -df for the
index category and -n for the page numbers.
*/

/* sort input lines */
int main(int argc, char *argv[])
{
  int nlines; /* number of input lines */
  int (*comparers[MAXARGS])(void *, void *) = {NULL};
  bool (*orderers[MAXARGS])(int) = {NULL};
  int (*wrappers[MAXARGS])(void *, void *, int (*comparer)(void *, void *)) = {NULL};

  if (argc == 1) {
    comparers[0] = (int (*)(void*, void*))strcmp;
    orderers[0] = order_forward;
    wrappers[0] = wrapper_strcmp_passthrough;
  } else if (argc > MAXARGS) {
    printf("Too many arguments.\n");
    return -1;
  } else {
    for(int arg_index = 1; arg_index < argc; arg_index++) {
      // -1 for index of pointer arrays, since we start from
      // arg 1
      get_comparers_and_orderer(argv[arg_index],
        &comparers[arg_index-1],
        &orderers[arg_index-1],
        &wrappers[arg_index-1]);
    }
  }

  if((nlines = readlines(lineptr, MAXLINES)) >= 0) {
    my_qsort((void*)lineptr, 0, nlines-1,
        comparers, orderers, wrappers);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("error: input too big to sort\n");
    return -2;
  }
}

int get_comparers_and_orderer(char *argument,
  int (**comparer)(void *, void *),
  bool (**iterator)(int),
  int (**wrapper_comparer)(void *, void *,int (*comparer)(void *, void *)))
{
  char current_argument_char;
  bool numeric, reverse_order, ignore_case, directory_order;
  numeric = reverse_order = ignore_case = directory_order = false;

  if (*argument != '-') {
    printf("Unknown option %s\n", argument);
    return 4;
  }

  // skip the leading dash
  argument++;

  while((current_argument_char = *argument++) != '\0') {
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
    *comparer = (int (*)(void*, void*))numcmp;
  } else if (ignore_case) {
    *comparer = (int (*)(void*, void*))strcmp_ignore_case;
  } else {
    //use default comparer if no args were specified
    *comparer = (int (*)(void*, void*))strcmp;
  }

  // see if we need a wrapper comparer
  *wrapper_comparer = (directory_order)
     ? wrapper_strcmp_directory
     : wrapper_strcmp_passthrough;

  *iterator = (reverse_order) ? order_reverse : order_forward;

  return 0;
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

static char allocbuf[ALLOCSIZE]; // Storage for alloc
static char *allocp = allocbuf; // Next free position

char *alloc(int n) // Return pointer to n characters
{
  if (allocbuf + ALLOCSIZE - allocp >= n) { // it fits
    allocp += n;
    return allocp - n;
  } else
    return 0;
}

size_t get_field(const char *line, char *field, int start_index) {
  char current;
  int result = 0;

  /* printf("starting generation: '%s' at index %d\n", line, start_index); */
  
  while((current = *(line + start_index + result)) != ' ' && current != '\0') {
    /* printf("\t%c\n", current); */
    field[result++] = current;
  }
  field[result] = '\0';

  /* printf("generated field '%s' from '%s'\n", field, line); */

  return result;
}

/* my_qsort: sort v[left]...v[right] into increasing order */
void my_qsort(void *v[], int left, int right,
    int (*comparers[])(void *, void *),
    bool (*orderers[])(int),
    int (*wrapper_comparers[])(void *, void *, int (*comparer)(void *, void *)))
{
  int i, last;
  void swap(void *v[], int i, int j);
  char fieldx[MAXLEN], fieldy[MAXLEN];

  if (left >= right) { /* do nothing if array contains */
    return;            /* fewer than two elements */
  }

  swap(v, left, (left + right)/2);
  last = left;
  for(i = left+1; i <= right; i++) {
    int current_comparison_value;
    int field_index = 0;
    int line_index_x = 0, line_index_y = 0;

    while(
      /* printf("test wrapper (field index: %d)\n", field_index) && */
      wrapper_comparers[field_index]
      &&
      /* printf("get fieldx\n") && */
      (line_index_x = get_field(v[i], fieldx, line_index_x))
      &&
      /* printf("get fieldy\n") && */
      (line_index_y = get_field(v[left], fieldy, line_index_y))
      &&
      (
       /* printf("comparison\n") && */
        (current_comparison_value =
          (*wrapper_comparers[field_index])(fieldx, fieldy, comparers[field_index])
        )
      )
      == 0) {
      field_index++;
      line_index_x++;
      line_index_y++;
      /* printf("not my fault\n"); */
      /* printf("fuck: %p\n", wrapper_comparers[field_index]); */
      /* printf("shit: %d\n", wrapper_comparers[field_index] == NULL); */
      /* printf("really not my fault\n"); */
    }

    /* printf("comparison result: %d\n", current_comparison_value); */
    /* int loop = current_comparison_value; */

    /* current_comparison_value = */
    /*   (*wrapper_comparers[field_index -1])(v[i], v[left], comparers[field_index -1]); */

    /* if (loop != current_comparison_value) { */
    /*   printf("++++++++++++\n"); */
    /*   printf("loop current_comparison_value: %d\n", loop); */
    /*   printf("current_comparison_value: %d\n", current_comparison_value); */
    /*   printf("i: %s left: %s\n", v[i], v[left]); */
    /* } */

    // if we have a non-zero comparison, run it by the ordering function
    // to see if we should swap
    if(current_comparison_value && (*orderers[field_index])(current_comparison_value)) {
      swap(v, ++last, i);
    }
  }
  swap(v, left, last);
  my_qsort(v, left, last - 1, comparers, orderers, wrapper_comparers);
  my_qsort(v, last+1, right, comparers, orderers, wrapper_comparers);
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
  /* printf("num 1: %s 2: %s\n", s1, s2); */

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

  *to = '\0';
}

static char modified1[MAXLEN], modified2[MAXLEN];

int wrapper_strcmp_directory(void *s1, void *s2,
    int (*inner_comparer)(void *, void *))
{
  char *s1mod = modified1;
  char *s2mod = modified2;

  copy_directory_chars(s1, s1mod);
  copy_directory_chars(s2, s2mod);

  /* printf("directory modified s1: '%s' s2: '%s'\n", s1, s2); */
  return (*inner_comparer)(modified1, modified2);
}

// transparent passthrough wrapper
int wrapper_strcmp_passthrough(void *s1, void *s2,
    int (*inner_comparer)(void *, void *))
{
  /* printf("passthrough: %s %s\n", s1, s2); */
  return (*inner_comparer)(s1, s2);
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

bool order_forward(int input)
{
  return input < 0;
}

// sort reverse using >
bool order_reverse(int input)
{
  return input > 0;
}
