#include <stdio.h>
#include <ctype.h>

/* make this really short for demonstration purposes */
#define MAX_LINE_LENGTH 20

int main()
{
  char c;
  int chars_in_line = 0;

  while((c = getchar()) != EOF) {
    if ((chars_in_line++ % MAX_LINE_LENGTH) == 0) {
      printf("\n");
    }

    if (c ==  '\n') {
      chars_in_line = 0;
    } else if (!isprint(c)) {
      printf("0x%X", c);
    } else {
      printf("%c", c);
    }
  }
  printf("\n");
}
