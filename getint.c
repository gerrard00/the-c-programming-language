#include <stdio.h>
#include <ctype.h>

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

/*getint:get next integer from input into *pn */
int getint(int *pn)
{
  int c, sign;

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
  *pn *= sign;
  if(c != EOF) {
    ungetc(c, stdin);
  }
  return c;
}

int main() 
{
  int return_value, converted;

  while((return_value = getint(&converted)) != EOF) {
    if (return_value) {
      printf("-> %8d\n", converted);
    }
  }
}
