#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

/* too lazy to get old code for getch and ungetch,
 * instead use built in getchar and ungetc */

void skip_non_digits() 
{
  char c;

  while(!isdigit(c = getchar()) &&  c != EOF)
    ;

  if (isdigit(c) || c == EOF) {
    ungetc(c, stdin);
  }
}

/*getfloat:get next floateger from input floato *pn */
int getfloat(float *pn)
{
  char c;
  int sign;
  float fractional_power;

  while(isspace(c = getchar())) /*skip white space */
    ;
  
  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
    /* it's not a number */
    skip_non_digits();
    return 0;
  }

  sign = (c == '-') ? -1 : 1;
  if(c== '+' || c== '-' ) {
    c = getchar();
    if (!isdigit(c)) {
      /* it's not a number */
      skip_non_digits();
      return 0;
    }
  }

  for (*pn =0; isdigit(c); c = getchar())
    *pn = 10 * *pn + (c-'0');

  //if c is a decimal, we may have a float. 
  //keep looking for digits.
  if (c == '.') {
    fractional_power = 1.0f;
    // skip the decimal. could use different loop, but
    // keep it similar to prevoius loop
    while(isdigit(c = getchar())) {
      *pn = 10 * *pn + (c-'0');
      fractional_power *= 10;
    }
    *pn /= fractional_power;
  }
  
  *pn *= sign;

  if(c != EOF) {
    ungetc(c, stdin);
  }

  return c;
}

int main() 
{
  float return_value, converted;

  while((return_value = getfloat(&converted)) != EOF) {
    if (return_value) {
      printf("-> %8f\n", converted);
    }
  }
}
