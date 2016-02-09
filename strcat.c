#include <stdio.h>
#include <string.h>

/*
Exercise 5-3. Write a pointer version of the function strcat that we showed
in Chapter 2: strcat (s,t) copies the string t to the end of s.
*/
char *my_strcat(char *s, const char *t) 
{
  char *x = s;

  while(*++s) {
    ;
  }

  while((*s++ = *t++)) {
    ;
  }

  return x;
}

int main() 
{
  char s[100] = "this is the first part";
  char *t = " and this is the second part";
  char *result;

  printf("before:\t%s\n", s);
  result = my_strcat(s, t);
  printf("after:\t%s\n", result);
}
