#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <assert.h>
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

  y_mask = (y & get_clear_mask(0, n)) << (p - n + 1);

  // first set our target section of x to all zeros,
  // then 'or' with our mask 
  return (x & ~get_clear_mask(p - n + 1, n)) | y_mask;
}

void test_setbits(unsigned x, int y, int p, int n, unsigned expected_result)
{
  unsigned result = setbits(x, p, n, y);

  printf("\nResults:\n\n");
  printf("\t%-15s", "Expected:");
  dump_bits(expected_result);
  printf("\t%-15s", "Actual:");
  dump_bits(result);
  assert(result == expected_result);
}

/*
Exercise 2-7. Write a function invert(x,p,n) that returns x with the n bits
that begin at position p inverted (i.e., 1 changed into 0 and vice versa), leaving
the others untouched.
*/
unsigned invert(unsigned x, int p, int n)
{
  unsigned inverted_mask = (~x & get_clear_mask(p - n + 1, n));

  return (x & ~get_clear_mask(p - n + 1, n)) | inverted_mask;
}

void test_invert(unsigned x, int p, int n, unsigned expected_result) 
{
  unsigned result = invert(x, p, n);

  printf("\nResults:\n\n");
  printf("\t%-15s", "Expected:");
  dump_bits(expected_result);
  printf("\t%-15s", "Actual:");
  dump_bits(result);
  assert(result == expected_result);
}

/*
Exercise 2-8. Write a function rightrot(x,n) that returns the value of the integer  rotated to the right by n  bit positions.
*/
//hacky...
int count_bits() 
{
  int x = 1; 
  int count = 1;

  while(x > 0) {
    x <<= 1;
    count++;
  }
  return count;
}

int rightrot(int x, int n) 
{
  static int number_of_bits_to_carry = 0;
  int carry;
  unsigned result = x;

  if (number_of_bits_to_carry == 0) {
    number_of_bits_to_carry = count_bits() - 1;
  }

  for(int i = 0; i < n; i++) {
    carry = (result & 1) << number_of_bits_to_carry;
    result = (result >> 1) | carry;
  }

  return result;
}

void test_rightrot(int x, int n, int expected_result) 
{
  int result = rightrot(x, n);

  printf("\nResults:\n\n");
  printf("\t%-15s", "Expected:");
  dump_bits(expected_result);
  printf("\t%-15s", "Actual:");
  dump_bits(result);
  printf("\n");
  assert(result == expected_result);
}

int main() 
{
  /* printf("%ld\n", strtol("11100000000000000000000000000001", NULL, 2)); */

  /* test_setbits(87, 458, 7, 4, 167); */
  /* test_setbits(144, 7, 5, 3, 184); */

  /* test_invert(170, 5, 4, 150); */
  /* test_invert(65280, 13, 2, 52992); */

  test_rightrot(strtol("00000000000000000000000000001111", NULL, 2),
    3,
    strtol("11100000000000000000000000000001", NULL, 2));

  test_rightrot(strtol("01000000000000000000000000001010", NULL, 2),
    5,
    strtol("01010010000000000000000000000000", NULL, 2));

  test_rightrot(strtol("00000000000000000000000010000000", NULL, 2),
    1,
    strtol("00000000000000000000000001000000", NULL, 2));
}

