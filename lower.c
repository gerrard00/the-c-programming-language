#include <stdio.h>
#include <string.h>
#include <assert.h>
/*
Exercise 2-10. Rewrite the function lower,which converts upper case
letters to lowercase, with a conditional expression instead of
if-else.
*/
void lower(char *input) 
{
  const int offset = 'A' - 'a';
  int len = strlen(input);

  for(int i = 0; i < len; i++) {
    input[i] = (input[i] >= 'A' && input[i] <= 'Z')
      ? input[i] - offset
      : input[i];
  }
}

void test_lower(char *input, const char *expected_result)
{
  printf("\nInput: %s\n", input);
  lower(input);
  printf("Output: %s\n", input);
  assert(strcmp(input, expected_result)  == 0);
}

int main() 
{
  char input1[] = "Test data.";
  test_lower(input1, "test data.");

  char input2[] = "This Is ALL CAPS";
  test_lower(input2, "this is all caps");
}
