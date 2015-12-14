#include <stdio.h>

#define IN 1  /* inside a word */
#define OUT 0 /* outside a word */
#define MAX_LENGTH 10 /* outside a word */

/* count lines, words and characters in input */
int main()
{
  int c, i, state, current_length;
  int lengths[10];

  state = OUT;
  current_length = 0;
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

  //NOTE: 
  for(i = 0; i < MAX_LENGTH; ++i) {
    printf("%d\t%d\n", i + 1, lengths[i]);
  }
}
