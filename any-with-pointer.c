#include <stdio.h>
#include <string.h>

/* return the first location in the string s1 where any character
 * from teh string s2 occurs. */
#define NOT_FOUND -1

int any(char s1[], char s2[]);

int main()
{
  char matching_input[] = "kids";
  char non_matching_input[] = "books";
  char target_chars[] = "di";
  int result;
  
  result = any(matching_input, target_chars);
  printf("Matching: %d\n", result);

  result = any(non_matching_input, target_chars);
  printf("Matching: %d\n", result);
}

int any(char s1[], char s2[])
{
  char *s1_ptr = s1;
  char *found_ptr;

  found_ptr = strpbrk(s1, s2);

  return (found_ptr == NULL)
    ? NOT_FOUND
    : found_ptr - s1_ptr;
}
