#include <stdio.h>
#include <string.h>

/* Exercise 2-4 Write an alternate version of squeeze(s1, s2) that
 * deletes each character in s1 that matches any character in the
 * string s2 */
#define NOT_FOUND -1

int indexOf(char search_for, char search_in[],
  int search_in_len);
void squeeze(char s1[], char s2[]);

int main() 
{
  char input[] = "This is a story about kids and floppy disks.";
  char target_chars[] = "isk";

  squeeze(input, target_chars);

  printf("%s\n", input);
}

void squeeze(char s1[], char s2[])
{
  int s1_len = strlen(s1);
  int s2_len = strlen(s2);
  int i, j;
  int found_index;

  for(i = j = 0; i < s1_len; i++) {
    found_index = indexOf(s1[i], 
        s2, 
        s2_len);

    if (found_index == NOT_FOUND) {
      s1[j++] = s1[i];
    }
  }

  s1[j] = '\0';
}

int indexOf(char search_for, char search_in[],
  int search_in_len)
{
  for(int i = 0; i < search_in_len; i++) {
    if (search_for == search_in[i]) {
      return i;
    }
  }

  return NOT_FOUND;
}
