#include <stdio.h>

#define IN 1
#define OUT 0

int main() 
{
  int c;
  int state;

  state = OUT;

  while((c = getchar()) != EOF) {
    putchar(c);

    if(c == ' ' || c == '\n') {
      if(state == IN) {
        putchar('\n');
      }
      state = OUT;
    } else {
      state = IN;
    }
  }
}
