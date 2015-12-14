#include <stdio.h>

int main() 
{
  int c, lastChar;

  lastChar = EOF;

  while((c = getchar()) != EOF) {
    if (c != ' ' || lastChar != ' ') {
      putchar(c);
      lastChar = c;
    }
  }
}
