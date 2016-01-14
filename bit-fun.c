#include <stdio.h>
#include "dump-bits.h"

unsigned getbits(unsigned x, int p, int n);

int main() 
{
  /* printf("077:\n"); */
  /* dump_bits(077); */
  /* printf("~077:\n"); */
  /* dump_bits(~077); */

  /* printf("12:\n"); */
  /* dump_bits(12); */
  /* printf("12:\n"); */
  /* dump_bits(12 & ~077); */

  const int target = 116;

  dump_bits(target);
  unsigned result = getbits(target, 4, 3);
  dump_bits(result);
}

unsigned getbits(unsigned x, int p, int n)
{
  return (x >> (p + 1 - n)) & ~(~0 << n) ;
}
