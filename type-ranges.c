#include <stdio.h>
#include <limits.h>
#include <float.h>

/* Exercise 2-1. Write a program to determine the ranges of char, short, int
 * and long variables, both signed and unsigned, by printing appropriate values
 * from standard headers and by direct computation. Harder if you compute them:
 * determine the ranges of the various floating-point types.*/
// note; my kingdom for macros, but not at that point in book
// note; not going to use math.h

const float FLOAT_INFINITY = 1.0f/0.0f;
const double DOUBLE_INFINITY = 1.0/0.0;
const double LONG_DOUBLE_INFINITY = 1.0l/0.0l;

void get_range_char(char *min, char *max);
void get_range_short(short *min, short *max);
void get_range_int(int *min, int *max);
void get_range_long(long *min, long *max);

int get_largest_exponent_float();
float pow_float(float signifigand, int exponent);
void get_max_float(float *max, int exponent);
void get_min_float(float *min, int exponent);

int get_largest_exponent_double();
double pow_double(double signifigand, int exponent); 
void get_max_double(double *max, int exponent);
void get_min_double(double *min, int exponent);

int get_largest_exponent_long_double();
long double pow_long_double(long double signifigand, int exponent);
void get_max_long_double(long double *max, int exponent);
void get_min_long_double(long double *min, int exponent);

int main() 
{
  printf("From headers:\n");
  printf("\tchar\t%20d\t%20d\n", SCHAR_MIN, SCHAR_MAX);
  printf("\t(u)char\t%20d\t%20d\n", 0, UCHAR_MAX);
  printf("\tshort\t%20d\t%20d\n", SHRT_MIN, SHRT_MAX);
  printf("\tushort\t%20d\t%20d\n", 0, USHRT_MAX);
  printf("\tint\t%20d\t%20d\n", INT_MIN, INT_MAX);
  printf("\tuint\t%20d\t%20u\n", 0, UINT_MAX);
  printf("\tlong\t%20ld\t%20ld\n", LONG_MIN, LONG_MAX);
  printf("\tulong\t%20d\t%20lu\n", 0, ULONG_MAX);
  
  printf("\nFrom computation:\n");
  char char_min, char_max;
  get_range_char(&char_min, &char_max);
  printf("\tchar\t%20d\t%20d\n", char_min, char_max);
  printf("\tuchar\t%20d\t%20d\n", 0, 2U * char_max + 1);
  short short_min, short_max;
  get_range_short(&short_min, &short_max);
  printf("\tshort\t%20d\t%20d\n", short_min, short_max);
  printf("\tushort\t%20d\t%20d\n", 0, 2U * short_max + 1);
  int int_min, int_max;
  get_range_int(&int_min, &int_max);
  printf("\tint\t%20d\t%20d\n", int_min, int_max);
  printf("\tuint\t%20d\t%20u\n", 0, 2U * int_max + 1);
  long long_min, long_max;
  get_range_long(&long_min, &long_max);
  printf("\tlong\t%20ld\t%20ld\n", long_min, long_max);
  printf("\tulong\t%20d\t%20lu\n", 0, 2U * long_max + 1);

  printf("\nFloat from headers:\n");
  printf("\tfloat\t%.10e\t%.10e\n", FLT_TRUE_MIN, FLT_MAX);
  printf("\tdouble\t%.10e\t%.10e\n", DBL_TRUE_MIN, DBL_MAX);
  printf("\tlong\t%.10Le\t%.10Le\n", LDBL_TRUE_MIN, LDBL_MAX);

  printf("\nFloat computation:\n");

  float flt_min, flt_max;
  int largest_exponent_float; 
  largest_exponent_float = get_largest_exponent_float();
  get_max_float(&flt_max, largest_exponent_float);
  get_min_float(&flt_min, largest_exponent_float);
  printf("\tfloat\t%.10e\t%.10e\n", flt_min, flt_max);

  double dbl_min, dbl_max;
  int largest_exponent_double;
  largest_exponent_double = get_largest_exponent_double();
  get_max_double(&dbl_max, largest_exponent_double);
  get_min_double(&dbl_min, largest_exponent_double);
  printf("\tdouble\t%.10e\t%.10e\n", dbl_min, dbl_max);

  long double ldbl_min, ldbl_max;
  int largest_exponent_long_double;
  largest_exponent_long_double = get_largest_exponent_long_double();
  get_max_long_double(&ldbl_max, largest_exponent_long_double);
  get_min_long_double(&ldbl_min, largest_exponent_long_double);
  printf("\tlong\t%.10Le\t%.10Le\n", ldbl_min, ldbl_max);
}

void get_range_char(char *min, char *max)
{
  char current, last;

  current = 1;
  last = 0;

  while (last < current) {
    last = current;
    current <<= 1;
  }

  *min = current;
  // Current is now at the bottom, 
  // so one below that is the top.
  *max = current - 1;
}

void get_range_short(short *min, short *max)
{
  short current, last;

  current = 1;
  last = 0;

  while (last < current) {
    last = current;
    current <<= 1;
  }

  *min = current;
  // Current is now at the bottom, 
  // so one below that is the top.
  *max = current - 1;
}

void get_range_int(int *min, int *max)
{
  int current, last;

  current = 1;
  last = 0;

  while (last < current) {
    last = current;
    current <<= 1;
  }

  *min = current;
  // Current is now at the bottom, 
  // so one below that is the top.
  *max = current - 1;
}

void get_range_long(long *min, long *max)
{
  long current, last;

  current = 1;
  last = 0;

  while (last < current) {
    last = current;
    current <<= 1;
  }

  *min = current;
  // Current is now at the bottom, 
  // so one below that is the top.
  *max = current - 1;
}

int get_largest_exponent_float() 
{
  int exponent;
  float value, last_value;

  exponent = 0;
  value = 1;
  last_value =  0;

  while (value != FLOAT_INFINITY &&
      value > last_value) {
    last_value = value;
    value *= 10; 
    ++exponent;
  }

  return --exponent;
}

int get_largest_exponent_double() 
{
  int exponent;
  double value, last_value;

  exponent = 0;
  value = 1;
  last_value =  0;

  while (value != DOUBLE_INFINITY &&
      value > last_value) {
    last_value = value;
    value *= 10; 
    ++exponent;
  }

  return --exponent;
}

int get_largest_exponent_long_double() 
{
  int exponent;
  long double value, last_value;

  exponent = 0;
  value = 1;
  last_value =  0;

  while (value != LONG_DOUBLE_INFINITY &&
      value > last_value) {
    last_value = value;
    value *= 10; 
    ++exponent;
  }

  return --exponent;
}

float pow_float(float signifigand, int exponent) 
{
  float result = signifigand;
  float multiplier;
  int i;

  if (exponent >= 0) {
    multiplier = 10;
  } else {
    multiplier = 0.1;
    exponent *= -1;
  }

  for(i = 0; i < exponent; i++) {
    result *= multiplier;
  }

  return result;
}

double pow_double(double signifigand, int exponent) 
{
  double result = signifigand;
  double multiplier;
  int i;

  if (exponent >= 0) {
    multiplier = 10;
  } else {
    multiplier = 0.1;
    exponent *= -1;
  }

  for(i = 0; i < exponent; i++) {
    result *= multiplier;
  }

  return result;
}

long double pow_long_double(long double signifigand, int exponent)
{
  long double result = signifigand;
  long double multiplier;
  int i;

  if (exponent >= 0) {
    multiplier = 10;
  } else {
    multiplier = 0.1;
    exponent *= -1;
  }

  for(i = 0; i < exponent; i++) {
    result *= multiplier;
  }

  return result;
}

void get_max_float(float *max, int largest_exponent)
{
  float signifigand, last_signifigand;
  float current_total, last_inner_total;
  float base_and_exponent;

  *max = 0;
  signifigand = 1;
  current_total = 1;
  base_and_exponent = pow_float(1, largest_exponent);

  while(signifigand < FLOAT_INFINITY && base_and_exponent > 0) {
    current_total = signifigand * base_and_exponent; 
    if (current_total > *max && current_total < FLOAT_INFINITY) {
      *max = current_total;
    }

    last_inner_total = 0;
    while(current_total < FLOAT_INFINITY 
        && last_inner_total != current_total) {
      last_signifigand = signifigand;
      signifigand++;
      last_inner_total = current_total;
      current_total = signifigand * base_and_exponent; 
    }
    signifigand = last_signifigand;

    base_and_exponent /= 10;
    signifigand *= 10;
  }
}

void get_min_float(float *min, int largest_exponent)
{
  float value, last_value;
  int divisor = 10;

  *min = value = pow_float(1, 0 - largest_exponent);
  /* printf("initial value: %.10e\n", value); */

  while (divisor > 1) {
    last_value = 0;
    while(value > 0 && value != last_value) { 
      last_value = value;

      if (value < *min) {
        *min = value;
        /* printf("\t\tmake min: %.10e\n", *min); */
      }
      value /= divisor;
    }

    value = *min;
    divisor--;
  }
}

void get_max_double(double *max, int largest_exponent)
{
  double signifigand, last_signifigand;
  double current_total, last_inner_total;
  double base_and_exponent;

  *max = 0;
  signifigand = 1;
  current_total = 1;
  base_and_exponent = pow_double(1, largest_exponent);

  while(signifigand < DOUBLE_INFINITY && base_and_exponent > 0) {
    current_total = signifigand * base_and_exponent; 
    if (current_total > *max && current_total < DOUBLE_INFINITY) {
      *max = current_total;
    }

    last_inner_total = 0;
    while(current_total < DOUBLE_INFINITY 
        && last_inner_total != current_total) {
      last_signifigand = signifigand;
      signifigand++;
      last_inner_total = current_total;
      current_total = signifigand * base_and_exponent; 
    }
    signifigand = last_signifigand;

    base_and_exponent /= 10;
    signifigand *= 10;
  }
}

void get_min_double(double *min, int largest_exponent)
{
  double value, last_value;
  int divisor = 10;

  *min = value = pow_double(1, 0 - largest_exponent);
  /* printf("initial value: %.10e\n", value); */

  while (divisor > 1) {
    last_value = 0;
    while(value > 0 && value != last_value) { 
      last_value = value;

      if (value < *min) {
        *min = value;
        /* printf("\t\tmake min: %.10e\n", *min); */
      }
      value /= divisor;
    }

    value = *min;
    divisor--;
  }
}

void get_max_long_double(long double *max, int largest_exponent)
{
  long double signifigand, last_signifigand;
  long double current_total, last_inner_total;
  long double base_and_exponent;

  *max = 0;
  signifigand = 1;
  current_total = 1;
  base_and_exponent = pow_long_double(1, largest_exponent);

  while(signifigand < DOUBLE_INFINITY && base_and_exponent > 0) {
    current_total = signifigand * base_and_exponent; 
    if (current_total > *max && current_total < DOUBLE_INFINITY) {
      *max = current_total;
    }

    last_inner_total = 0;
    while(current_total < DOUBLE_INFINITY 
        && last_inner_total != current_total) {
      last_signifigand = signifigand;
      signifigand++;
      last_inner_total = current_total;
      current_total = signifigand * base_and_exponent; 
    }
    signifigand = last_signifigand;

    base_and_exponent /= 10;
    signifigand *= 10;
  }
}

void get_min_long_double(long double *min, int largest_exponent)
{
  long double value, last_value;
  int divisor = 10;

  *min = value = pow_long_double(1, 0 - largest_exponent);
  /* printf("initial value: %.10e\n", value); */

  while (divisor > 1) {
    last_value = 0;
    while(value > 0 && value != last_value) { 
      last_value = value;

      if (value < *min) {
        *min = value;
        /* printf("\t\tmake min: %.10e\n", *min); */
      }
      value /= divisor;
    }

    value = *min;
    divisor--;
  }
}
