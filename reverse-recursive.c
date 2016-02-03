#include <stdio.h>
#include <string.h>

/*
Exercise 4-13. Write a recursive version of the function reverse(s),
which reversesthe string s in place.
*/
void real_reverse(char s[], int left_index, int right_index)
{
  char temp = s[left_index];
  s[left_index] = s[right_index];
  s[right_index] = temp;

  ++left_index;
  --right_index;

  if (left_index < right_index) {
    real_reverse(s, left_index, right_index);
  }
}

void reverse(char s[]) 
{
  real_reverse(s, 0, strlen(s) - 1);
}
int main() 
{
  char input[] = "Gerrard";

  printf("before: %s\n", input);
  reverse(input);
  printf("after: %s\n", input);

  char input2[] = "hotrod";
  printf("before: %s\n", input2);
  reverse(input2);
  printf("after: %s\n", input2);
}
