#include <stdio.h>
#include "dump-bits.h"

int main() 
{
  printf("077:\n");
  dump_bits(077);
  printf("~077:\n");
  dump_bits(~077);

  printf("12:\n");
  dump_bits(12);
  printf("12:\n");
  dump_bits(12 & ~077);
}
