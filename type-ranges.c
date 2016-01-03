#include <stdio.h>
#include <limits.h>
#include <float.h>

/* Exercise 2-1. Write a program to determine the ranges of char, short, int
 * and long variables, both signed and unsigned, by printing appropriate values
 * from standard headers and by direct computation. Harder if you compute them:
 * determine the ranges of the various floating-point types.*/
// my kingdom for macros, but not at that point in book

const float FLOAT_INFINITY = 1.0f/0.0f;
const double DOUBLE_INFINITY = 1.0/0.0;
const double LONG_DOUBLE_INFINITY = 1.0l/0.0l;

void get_range_char(char *min, char *max);
void get_range_short(short *min, short *max);
void get_range_int(int *min, int *max);
void get_range_long(long *min, long *max);
void get_range_float(float *min, float *max);
void get_range_double(double *min, double *max);
void get_range_long_double(long double *min, long double *max);

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
  printf("\tfloat\t%.10e\t%.10e\n", FLT_MIN, FLT_MAX);
  printf("\tdouble\t%.10e\t%.10e\n", DBL_MIN, DBL_MAX);
  printf("\tlong\t%.10Le\t%.10Le\n", LDBL_MIN, LDBL_MAX);

  //TODO: find ranges bycomputation for float
  printf("\nFloat computation:\n");
  float flt_min, flt_max;
  get_range_float(&flt_min, &flt_max);
  printf("\tfloat\t%.10e\t%.10e\n", flt_min, flt_max);
  double dbl_min, dbl_max;
  get_range_double(&dbl_min, &dbl_max);
  printf("\tdouble\t%.10e\t%.10e\n", dbl_min, dbl_max);
  long double ldbl_min, ldbl_max;
  get_range_long_double(&ldbl_min, &ldbl_max);
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

//this would be easier with pow
float get_largest_exponent_float() 
{
  float exponent, last_exponent;

  exponent = 1;
  last_exponent =  0;
  while (exponent != FLOAT_INFINITY &&
      exponent > last_exponent) {
    last_exponent = exponent;
    exponent *= 10; 
  }
  return last_exponent;
}

void get_range_float(float *min, float *max)
{
  float exponent;
  float signifigand, last_signifigand;
  float current_total, last_inner_total;

  exponent = get_largest_exponent_float();

  *max = 0;
  signifigand = 1;
  current_total = 1;

  while(signifigand < FLOAT_INFINITY && exponent > 0) {
    current_total = signifigand * exponent; 
    if (current_total > *max && current_total < FLOAT_INFINITY) {
      *max = current_total;
    }

    last_inner_total = 0;
    while(current_total < FLOAT_INFINITY 
        && last_inner_total != current_total) {
      last_signifigand = signifigand;
      signifigand++;
      last_inner_total = current_total;
      current_total = signifigand * exponent; 
    }
    signifigand = last_signifigand;

    exponent /= 10;
    signifigand *= 10;
  }

  //TODO: need min
  *min = 0;
}

double get_largest_exponent_double() 
{
  double exponent, last_exponent;

  exponent = 1;
  last_exponent =  0;
  while (exponent != DOUBLE_INFINITY &&
      exponent > last_exponent) {
    last_exponent = exponent;
    exponent *= 10; 
  }
  return last_exponent;
}

void get_range_double(double *min, double *max)
{
  double exponent;
  double signifigand, last_signifigand;
  double current_total, last_inner_total;

  exponent = get_largest_exponent_double();

  *max = 0;
  signifigand = 1;
  current_total = 1;

  while(signifigand < DOUBLE_INFINITY && exponent > 0) {
    current_total = signifigand * exponent; 
    if (current_total > *max && current_total < DOUBLE_INFINITY) {
      *max = current_total;
    }

    last_inner_total = 0;
    while(current_total < DOUBLE_INFINITY 
        && last_inner_total != current_total) {
      last_signifigand = signifigand;
      signifigand++;
      last_inner_total = current_total;
      current_total = signifigand * exponent; 
    }
    signifigand = last_signifigand;

    exponent /= 10;
    signifigand *= 10;
  }

  //TODO: need min
  *min = 0;
}

long double get_largest_exponent_long_double() 
{
  long double exponent, last_exponent;

  exponent = 1;
  last_exponent =  0;
  while (exponent != LONG_DOUBLE_INFINITY &&
      exponent > last_exponent) {
    last_exponent = exponent;
    exponent *= 10; 
  }
  return last_exponent;
}

void get_range_long_double(long double *min, long double *max)
{
  long double exponent;
  long double signifigand, last_signifigand;
  long double current_total, last_inner_total;

  exponent = get_largest_exponent_long_double();

  *max = 0;
  signifigand = 1;
  current_total = 1;

  while(signifigand < LONG_DOUBLE_INFINITY && exponent > 0) {
    current_total = signifigand * exponent; 
    if (current_total > *max && current_total < LONG_DOUBLE_INFINITY) {
      *max = current_total;
    }

    last_inner_total = 0;
    while(current_total < LONG_DOUBLE_INFINITY 
        && last_inner_total != current_total) {
      last_signifigand = signifigand;
      signifigand++;
      last_inner_total = current_total;
      current_total = signifigand * exponent; 
    }
    signifigand = last_signifigand;

    exponent /= 10;
    signifigand *= 10;
  }

  //TODO: need min
  *min = 0;
}
