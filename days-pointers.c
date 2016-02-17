#include <stdio.h>
/*
Exercise 5-9. Rewrite the routines day_of_year and month_day with
pointers instead of indexing.
*/

#define MIN_MONTH 1
#define MAX_MONTH 12 

//TODO: make the 0th elements 0 again
static char daytab[2][13] = {
  { 68, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  { 69, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

static int max_days_in_year[2] = { 365, 366 };

char get_leap(int year) 
{
  return (year%4 == 0 && year%100 != 0) || year%400 == 0;
}

char get_daytab_value(int leap, int month)
{
  //TODO: that's ugly, I must not be grokking this.
  // daytab is an array of arrays of char, i.e. a pointer
  // to a pointer to char. So, can't just do pointer math 
  // on daytab directly to index the child elements of each 
  // child array
  return *((*(daytab + leap)) + month);
}

/* day_of_year:set day of year from month & day */
int day_of_year(int year, int month, int day)
{
  int i, leap;

  leap = get_leap(year);

  if (month < MIN_MONTH ||  month > MAX_MONTH) {
    printf("->Invalid month %d\n", month);
    return -1;
  }

  if (day < 1 || day > daytab[leap][month]) {
    printf("->Invalid day %d for month %d\n", day, month);
    return -2;
  }

  for (i = 1; i < month; i++) {
    day += get_daytab_value(leap, i);
  }
  return day;
}

/* month_day: set monh, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday) 
{
  int i, leap;

  leap = get_leap(year);

  if (yearday < 1 || yearday > max_days_in_year[leap]) {
    printf("->Invalid day of year %d for year %d\n", yearday, year);
    *pmonth = -1;
    *pday = -1;
    return;
  }

  for(i = 1; yearday > daytab[leap][i]; i++) 
    yearday -= get_daytab_value(leap, i);
  *pmonth = i;
  *pday = yearday;
}

int main() 
{
  int doy, month, day;

  doy = day_of_year(2016, 2, 16);
  printf("doy: %d\n", doy);

  month_day(2016, doy, &month, &day);
  printf("month/day: %2d/%2d\n", month, day);

  /* invalid month */
  doy = day_of_year(2016, 13, 16);
  printf("invalid month doy: %d\n", doy);

  doy = day_of_year(2016, 2, 30);
  printf("invalid day of month doy: %d\n", doy);

  // 2015 was not a leap year
  month_day(2015, 366, &month, &day);
  printf("invalid month/day: %2d/%2d\n", month, day);
}
