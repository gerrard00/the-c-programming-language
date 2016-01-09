#include <stdio.h>
#include <string.h>

/* Exercise 2-4 Write an alternate version of squeeze(s1, s2) that
 * deletes each character in s1 that matches any character in the
 * string s2 */

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
  int i, j;
  char *found_index;

  for(i = j = 0; i < s1_len; i++) {
    found_index = strchr(s2, s1[i]);

    if (found_index == NULL) {
      s1[j++] = s1[i];
    }
  }

  s1[j] = '\0';
}
