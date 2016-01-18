#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define MAX_SIZE 1000

bool is_range_character(char candidate)
{
  return (candidate >= 'A'  && candidate <= 'Z')
    || (candidate >= 'a'  && candidate <= 'z')
    || (candidate >= '0'  && candidate <= '9');
}

/*
Exercise 3-3. Write a function expand(s1, s2) that expands shorthand 
notation like a-z in the string s1 into the equivalent complete list
abc...xyz in s2. Allower for letters of either case and digits, and
be preprared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange
that a leading or trailing - is taken literally.
*/
void expand(char s1[], char s2[]) 
{
  int i, j;
  char current_char, last_char, next_char;
  int len = strlen(s1);

  last_char = '\0';

  for(i = 0, j = 0; i < len; i++, j++) {
    current_char = s1[i];

    if (current_char == '-'
        // check for leading
        && is_range_character(last_char)
        // check for trailing
        && ((i == len - 1) || is_range_character(s1[i + 1]))
       ) {

      /* printf("last %c\n", last_char); */
      /* printf("current %c\n", current_char); */
      next_char = s1[i + 1];
      /* printf("next %c\n", next_char); */

      for(char expansion_char = last_char + 1; 
         expansion_char < next_char; 
          expansion_char++, j++) {
        s2[j] = expansion_char;
      }
      // reset j, since we went one too far in the inner loop
      j--;
    } else {
      s2[j] = current_char;
      last_char = current_char;
    }
  }
  
  s2[j] = '\0';
}

void test_expand(char s1[], char s2[], char expected[])
{
  expand(s1, s2);
  printf("result:   %s\n", s2);
  printf("expected: %s\n\n", expected);
  assert(strcmp(s2, expected) == 0);
}


int main() 
{
  char s2[MAX_SIZE];

  char s1a[] ="test a-z";
  test_expand(s1a, s2, "test abcdefghijklmnopqrstuvwxyz");

  char s1b[] ="test g-l";
  test_expand(s1b, s2, "test ghijkl");

  char s1c[] ="test 0-9 is a number test.";
  test_expand(s1c, s2, "test 0123456789 is a number test.");

  char s1d[] ="test 3-7 is a number test.";
  test_expand(s1d, s2, "test 34567 is a number test.");

  char s1e[] ="this is a big a-zA-Z0-9 test";
  test_expand(s1e, s2, "this is a big abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 test");

  char s1f[] ="this has both -leading and trailing- hyphens.";
  test_expand(s1f, s2, "this has both -leading and trailing- hyphens.");

  char s1g[] ="a-b-c";
  test_expand(s1g, s2, "abc");

  char s1h[] ="-a-z";
  test_expand(s1h, s2, "-abcdefghijklmnopqrstuvwxyz");

  char s1i[] ="--";
  test_expand(s1i, s2, "--");
}
