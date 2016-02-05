#include <stdio.h>

/*
Exercise 4-14. Define a macro swap(t,x,y) that interchanges two 
arguments of type t.(Blockstructure will help.)
*/
#define swap(t, x, y) t temp = x; \
  x = y; \
  y = temp 
                               

int main() 
{
  int a = 7;
  int b = 13;

  printf("a: %d b: %d\n", a, b);

  swap(int, a, b);

  printf("a: %d b: %d\n", a, b);
}
