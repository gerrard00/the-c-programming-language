#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

//TODO: really determine this, just picked a brown number
#define MAX_CHARS_IN_INPUT = 10
/* http://stackoverflow.com/a/8257728/1011470 */
#define SAFE_INT_STRING_SIZE ((CHAR_BIT * sizeof(int) - 1) / 3 + 2)

int hextoi(const char *input);

int main() 
{
  char hex_string[SAFE_INT_STRING_SIZE];
  int result;

  printf("Test 1\n");
  printf("\n");

  for(int i =0; i <= 32000; i++) {
    sprintf(hex_string, "%04x", i);
    result = hextoi(hex_string);
    if (i % 1000 == 0) printf("Result: %d\t\t%s\n", result, hex_string);
    assert(result == i);
  }
}

int hextoi(const char *input)
{
  //TODO: error handling

  int result, i, start_index, end_index;

  //if the string starts with "0x" we don't need to
  //process those chars
  start_index = (input[0] == '0' && input[1] == 'x') 
    ? 2 : 0;

  end_index = strlen(input) - 1;
  
  result = 0;

  for(i = start_index; i <= end_index; i++) {
    result *= 16;

    if (isdigit(input[i])) {
      result += input[i] - '0';
    } else if (isupper(input[i])) {
      result += (input[i] - 'A') + 10;
    } else {
      result += (input[i] - 'a') + 10;
    }
  }
  return result;
}
