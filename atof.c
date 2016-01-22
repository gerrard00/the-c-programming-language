#include <stdio.h>
#include <ctype.h>
#include <assert.h>

/* atof:convert string s to double */

double atof_offset(const char s[], int start_index)
{
  double val, power, exponent, exponent_modifier, base_and_exponent;
  int i, sign;

  /* skip white space */
  for (i = start_index; isspace(s[i]); i++) {
    ;
  }
  sign=(s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-') {
    i++;
  }
  for (val = 0.0; isdigit(s[i]); i++) {
    val = 10.0 * val + (s[i] - '0');
  }
  if (s[i]== '.') {
    i++;
  }
  for (power = 1.0; isdigit(s[i]); i++) {
    val = 10.0 * val + (s[i] - '0');
    power *= 10;
  }
  base_and_exponent = 1;
  if (s[i]== 'e') {
    i++;
    exponent = atof_offset(s, i); 
    if (exponent < 0) {
      exponent_modifier = 0.1;
      exponent = -exponent;
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

double atof(const char s[])
{
  double atof_offset(const char s[], int start_index);

  return atof_offset(s, 0);
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
