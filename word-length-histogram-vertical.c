#include <stdio.h>

#define IN 1  /* inside a word */
#define OUT 0 /* outside a word */
#define MAX_LENGTH 10 /* outside a word */

/* count lines, words and characters in input */
int main()
{
  int c, i, j, state, current_length;
  int max_recorded_length, bar_length;
  int lengths[10];

  state = OUT;
  current_length = max_recorded_length = 0;
  for(i = 0; i < MAX_LENGTH; ++i) {
    lengths[i] = 0;
  }

  while((c = getchar()) != EOF) {
    if (c == ' ' || c == '\n' || c == '\t') {
      state = OUT;
      if (current_length > MAX_LENGTH) {
        current_length = MAX_LENGTH;
      }
      ++lengths[current_length - 1];
      current_length = 0;
    } else {
      state = IN;
      ++current_length;
    }
  }

  for(i = 0; i < MAX_LENGTH; ++i) {
    if (lengths[i] > max_recorded_length) {
      max_recorded_length = lengths[i];
    }
  }

  printf("\n");

  for(bar_length = max_recorded_length;
      bar_length > 0; --bar_length) {

    printf("%3d ", bar_length);
    for(i = 0; i < MAX_LENGTH; ++i) {
      if (lengths[i] >= bar_length) {
        printf(" * ");
      } else {
        printf("   ");
      }
    }
    printf("\n");
  }

  printf("CNT ");
  for(i = 0; i < MAX_LENGTH; ++i) {
    printf("%2d ", i + 1);
  }
  printf("\n");
}
