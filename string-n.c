#include <stdio.h>
#include <string.h>

/*
Exercise 5-5. Write versions of the library functions strncpy, strncat,and
strncmp; which operate on at most the first n characters of their argument
strings. For example,strncpy(s,t ,n) copies at most n characters of t to s.
Full descriptionsare in Appendix B.0
*/

char *my_strncpy(char *s, const char *t, int n)
{
  char *original_s = s;
  int i;

  for(i = 0; i < n && (*s++ = *t++); i++) {
    ;
  }

  *s = '\0';

  //TODO: pad the rest of s with null?
  return original_s;
}

void test_strncpy()
{
  char s[1000]; 
  char t[] = "gerrard";
  char *result;
  int n;

  n = 0;
  result = my_strncpy(s, t, n);
  printf("%d: %s\n", n, result);
  memset(s, '\0', sizeof(s));

  n = 3;
  result = my_strncpy(s, t, n);
  printf("%d: %s\n", n, result);
  memset(s, '\0', sizeof(s));

  n = 5;
  result = my_strncpy(s, t, n);
  printf("%d: %s\n", n, result);
  memset(s, '\0', sizeof(s));

  n = 7;
  result = my_strncpy(s, t, n);
  printf("%d: %s\n", n, result);
  memset(s, '\0', sizeof(s));

  n = 35;
  result = my_strncpy(s, t, n);
  printf("%d: %s\n", n, result);
  memset(s, '\0', sizeof(s));
}

char *my_strcatn(char *s, const char *t, int n) 
{
  char *x = s;
  int i;

  while(*++s) {
    ;
  }

  for(i = 0; i < n && (*s++ = *t++); i++) {
    ;
  }

  //if we didn't get an ending char, add one
  if (*s) {
    *s = '\0';
  }

  return x;
}

void test_strcatn()
{
  char s0[] = "this is the first part";
  char s1[] = "this is the first part";
  char s2[] = "this is the first part";
  char *t = " and this is the second part";
  char *result;
  int n;

  printf("before:\t%s\n", s0);

  n = 0;
  result = my_strcatn(s0, t, n);
  printf("after (%d):\t\"%s\"\n", n, result);

  n = 4;
  result = my_strcatn(s1, t, n);
  printf("after (%d):\t\"%s\"\n", n, result);

  n = 100;
  result = my_strcatn(s2, t, n);
  printf("after (%d):\t\"%s\"\n", n, result);
}

int main() 
{
  /* test_strncpy(); */
  test_strcatn();
}
