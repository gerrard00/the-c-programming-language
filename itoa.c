#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include  <stdbool.h>

/*
  Exercise 3-4. In a two's complement number representation, our version of
  itoa does not handle the largest negative number, that is, the value of n equal
  to -(2wordsize-l). Explain why not. Modify it to print that value correctly,
  regardless of the machine on which it runs.
*/

/*
The largest negative number can't be negated in order to get a positive number.
The negative of the largest number is the same negative number.

e.g. in a 3 bit system -4 is the smallest negative (100)

to negate it in twos complement,we take the ones complement (011)
and add 1 (001)
which gives us (100 again)
*/
void reverse(char s[])
{
  char temp;
  int middle_index, i, target_index;
  int length = strlen(s);
  
  middle_index = length/2;

  for(i = 0; i < middle_index; i++) {
    target_index = length - i - 1;
    temp = s[i];
    s[i] = s[target_index];
    s[target_index] = temp;
  }
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[])
{
	int i, sign;

	if ((sign=n) < 0) /* record sign */
		n=-n; /* make n positive  */
	i=0;
	do {
		/* generate digits in reverse order */
		s[i++]=n%10+'0'; /* get next digit*/
	} while ((n /= 10) > 0);	/*delete it*/
	if (sign < 0)
		s[i++]= '-';
	s[i]='\0';
  reverse(s);
 }

/* what if there is a machine without a larger integer type? */
void itoa_mine(int n, char s[])
{
	int i, sign;
  // we have to handle the most negative number differently
  bool is_most_negative = false;

  /* record sign */
	if ((sign=n) < 0) {
		n=-n; /* make n positive  */

    // sign has the orignal value
    if (sign == n) {
      //this is the most negative number
      //let's handle if as if it was one larger
      is_most_negative = true; 
      n++;
      n=-n;
    }
  }

	i=0;
	do {
		/* generate digits in reverse order */
		s[i++]= n % 10 + '0'; /* get next digit*/
	} while ((n /= 10) > 0);	/*delete it*/

  if (is_most_negative) {
    // we processed the number as if it was 
    // one larger (less negative) than it
    // really is
    s[0] += 1;
  }

	if (sign < 0)
		s[i++]= '-';
	s[i]='\0';
  reverse(s);
 }

void test(int n)
{
	char s1[1000], s2[1000];
	itoa(n, s1);
	itoa_mine(n, s2);
	printf("%12s\t%12s\n", s1, s2);
}

int main() 
{
	int n;

	n = 0;
  test(n);
  
	n = 1;
  test(n);

	n = 1776;
  test(n);

	n = -157;
  test(n);

	n = INT_MIN + 1;
  test(n);

	n = INT_MIN + 1;
  test(n);

	n = INT_MIN;
  test(n);

  printf("*************************\n");
  printf("%12d\n", INT_MIN);

	printf("Done!\n");	
}
