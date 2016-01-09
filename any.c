#include <stdio.h>
#include <string.h>

/* return the first location in the string s1 where any character
 * from teh string s2 occurs. */
#define NOT_FOUND -1

int any(char s1[], char s2[]);
int indexOf(char search_for, char search_in[]);

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
  int s2_len = strlen(s2);
  int current_index;
  int result = NOT_FOUND;

  for(int i = 0; i < s2_len; i++) {
    current_index = indexOf(s2[i], s1);

    if (result == NOT_FOUND 
        || (current_index != NOT_FOUND 
            && current_index < result)) {

      result = current_index; 
    }
  }

  return result;
}

int indexOf(char search_for, char search_in[])
{
  int search_in_len = strlen(search_in);

  for(int i = 0; i < search_in_len; i++) {
    if (search_for == search_in[i]) {
      return i;
    }
  }

  return NOT_FOUND;
}
