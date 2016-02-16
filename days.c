#include <stdio.h>
/*
Exercise 5-8. There is no error checking inday_of _yearormonth_day.
Remedy this defect.
*/

#define MIN_MONTH 1
#define MAX_MONTH 12 

static char daytab[2][13] = {
  { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
  { 0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

static int max_days_in_year[2] = { 365, 366 };

int get_leap(int year) 
{
  return (year%4 == 0 && year%100 != 0) || year%400 == 0;
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
    day += daytab[leap][i];
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
    yearday -= daytab[leap][i];
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
