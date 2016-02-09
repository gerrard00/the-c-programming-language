#include <stdio.h>

/*
Exercise 5-4. Write the function strend (s,t),which returns 1 if the string
t occurs at the end of the string s,and zero otherwise.
*/
int strend(const char *s, const char *t)
{
  const char *original_t = t;

  while(*s++) {
    ;
  }

  while(*t++) {
    ;
  }

  while(*s-- == *t-- && t >= original_t) {
  }

  // if we didn't make it back to the starting
  // position we don't have a match
  return (t > original_t) ? 0 : 1;
}

int main()
{
  const char *x = "this ends";
  int result;

  result = strend(x, "ends");
  printf("has it: %d\n", result);

  result = strend(x, "finishes");
  printf("doesn't have it: %d\n", result);

  result = strend(x, "0nds");
  printf("almost has it: %d\n", result);
}
