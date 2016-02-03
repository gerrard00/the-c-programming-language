#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include  <stdbool.h>

/*
Exercise 4-12. Adapt the ideas of printd to write a recursive version of itoa;
that is, convert an integer into a string by calling a recursive routine.
*/

int itoa_imp(int original, int n, char s[], int current_index)
{
  int current_value;
  int remaining;

  current_value = n % 10;
  remaining = n / 10;

  if (remaining > 0) {
    current_index = itoa_imp(original, remaining, s, current_index);
  }

  s[current_index++] = current_value + '0';

  if (original == n) {
    s[current_index] = '\0';
  }

  return current_index;
}

void itoa(int n, char s[])
{
  int index = 0;

  if (n < 0) {
    n = -n;
    s[index++] = '-';
  }

  itoa_imp(n, n, s, index);
}

void test(int n)
{
	char s1[1000];
	itoa(n, s1);
	printf("%15d\t%15s\n", n, s1);
}

int main() 
{
	int n;

	n = 0;
  test(n);
  
	n = 7;
  test(n);

	n = 76;
  test(n);

	n = 33;
  test(n);

	n = 34;
  test(n);
  
	n = 1776;
  test(n);

	n = -157;
  test(n);

	n = INT_MIN + 1;
  test(n);

	printf("\nDone!\n");	
}
