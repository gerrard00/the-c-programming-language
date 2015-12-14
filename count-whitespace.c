#include <stdio.h>

int main() 
{
  int c, nl, tb, bl;

  nl = 0;
  tb = 0;
  bl = 0;

  while((c = getchar()) != EOF) {
    switch(c) {
      case '\n':
        ++nl;
        break;
      case '\t':
        ++tb;
        break;
      case ' ':
        ++bl;
        break;
    }
  }

  printf("\nBlanks: %d\n", bl);
  printf("\nTabs: %d\n", tb);
  printf("\nNewlines: %d\n", nl);
}
