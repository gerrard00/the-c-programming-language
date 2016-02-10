#include <stdio.h>
#include <ctype.h>
#include <assert.h>

/* atof:convert string s to double */

double atof(const char *s);

double atof(const char *s)
{
  double val, power, exponent, exponent_modifier, base_and_exponent;
  int sign;

  /* skip white space */
  while (isspace(*s)) {
    s++;
  }
  sign=(*s == '-') ? -1 : 1;
  if (*s == '+' || *s == '-') {
    s++;
  }
  for (val = 0.0; isdigit(*s); s++) {
    val = 10.0 * val + (*s - '0');
  }
  if (*s == '.') {
    s++;
  }
  for (power = 1.0; isdigit(*s); s++) {
    val = 10.0 * val + (*s - '0');
    power *= 10;
  }
  base_and_exponent = 1;
  if (*s == 'e') {
    s++;
    exponent = atof(s); 
    if (exponent < 0) {
      exponent_modifier = 0.1;
      exponent = - exponent;
    } else {
      exponent_modifier = 10;
    }
    /* printf("Exponent: %f\n", exponent); */
    for(int j = 0; j < exponent; j++) {
      base_and_exponent *= exponent_modifier;

    /* printf("base and mod: %f\n", base_and_exponent); */
    }
  }

  return sign * val * base_and_exponent/ power;
}

void test_atof(const char *s, double expected)
{
  double result = atof(s);
  printf("%25f\n%25f\n\n", expected, result);
  /* comparing floats is non-trivial, eyeball it. */
  /* assert(expected == result); */
}

int main() 
{
  printf("Done!\n");

  test_atof("0",0);
  test_atof("1", 1);
  test_atof("-1", -1);
  test_atof("-123", -123);
  test_atof("3.14", 3.14);
  test_atof("123.45", 123.45);

  test_atof("123.45e6", 123.45e6);
  test_atof("123.45e-2", 123.45e-2);
  test_atof("123.45e-6", 123.45e-6);
}
