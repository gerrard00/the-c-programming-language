#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <assert.h>
#include  <stdbool.h>

/*
Exercise 3-5. Write the function itob(n,s ,b) that converts the integer
n into a base b character representation in the string s.In particular,
itob (n,s,16) formats n as a hexadecimal integer in s.
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

const char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
  'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
  'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

/* itob: convert n to characters in s with base b */
void itob(int n, char s[], int b)
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
		s[i++]= digits[n % b]; /* get next digit*/
	} while ((n /= b) > 0);	/*delete it*/

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
	itob(n, s1, 10);
	itob(n, s2, 16);
	itob(n, s2, 2);
  //TODO: test base 2
	printf("%12s\t%12s\n", s1, s2);
}

int main() 
{
	int n;

	n = 0;
  test(n);
  
	n = 1;
  test(n);

	n = 6;
  test(n);

	n = 255;
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
