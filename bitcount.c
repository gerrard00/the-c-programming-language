#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
#include "dump-bits.h"

/*
Exercise 2-9. In a two's complement number system, x &= (x-1) deletes the reightmost 1-bit in x.
Explain why. Use this observation to write a faster version of bitcount.
*/
int bitcount(unsigned x) 
{
  // x &= (x -1) deletes the rightmost 1-bt in x, because decreasing
  // a number by 1 requires flipping at least one bit to zero. If
  // bits to the right of the bit that flips to zero are flipped to
  // one, they will be eliminated by the and operation.
  int count;

  for(count = 0; 
      x != 0;
      x &= (x - 1), count++);

  return count;
}

void test_bitcount(unsigned x, int expected_result) 
{
  int result = bitcount(x);

  printf("\nResults:\n\n");
  printf("\t%-15s: %d\n", "Expected:", expected_result);
  printf("\t%-15s: %d\n", "Actual:", result);
  printf("\n");
  assert(result == expected_result);
}

int main() 
{
  /* printf("%ld\n", strtol("11100000000000000000000000000001", NULL, 2)); */

  test_bitcount(strtol("00111110000000000000000000001111", NULL, 2),
    9);

  test_bitcount(strtol("00000000010000000000000000000000", NULL, 2),
    1);

  test_bitcount(strtol("00000000000000000000000000000000", NULL, 2),
    0);
}

