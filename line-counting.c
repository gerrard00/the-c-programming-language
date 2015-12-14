#include <stdio.h>

int main() 
{
  int c, nl;
  int sawSomeChars;

  nl = 0;
  sawSomeChars = 0;

  while((c = getchar()) != EOF) {
    sawSomeChars = 1;

    if (c == '\n') {
      ++nl;
    }
  }

  if (sawSomeChars) {
    ++nl;
  }

  printf("\n%d\n", nl);
}
