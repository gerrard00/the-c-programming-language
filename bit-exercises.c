#include <stdio.h>
#include <stdlib.h>
#include "dump-bits.h"

unsigned get_clear_mask(int p, int n) 
{
  return (~(~0 << n)) << p;
}

/*
Exercise 2-6. Write a function setbits(x,p,n.y) that returns x ith the n
bits that begin at position p set to the rightmost n bits of y, leaving 
the other bits unchanged.
*/
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
  unsigned y_mask;

  /* printf("\n"); */
  /* printf("x:\t"); */
  /* dump_bits(x); */
  /* printf("y:\t"); */
  /* dump_bits(y); */
  /* printf("\n"); */

  /* printf("clear input:\t"); */
  /* dump_bits(get_clear_mask(p - n + 1, 4)); */

  y_mask = (y & get_clear_mask(0, 4)) << (p - n + 1);
  /* printf("y mask:\t"); */
  /* dump_bits(y_mask); */

  // first set our target section of x to all zeros,
  // then 'or' with our mask 
  return (x & ~get_clear_mask(p - n + 1, 4)) | y_mask;
}

void test_setbits(unsigned x, int y, int p, int n, unsigned expected_result)
{
  unsigned result = setbits(x, p, n, y);

  printf("\nResults:\n\n");
  printf("%-15s", "Expected:");
  dump_bits(expected_result);
  printf("%-15s", "Actual:");
  dump_bits(result);
}

int main() 
{
  test_setbits(87, 458, 7, 4, 167);

  /* printf("%ld\n", strtol("0101", NULL, 2)); */
}

