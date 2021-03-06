#include <stdio.h>

int convertToFahrenheit(int celsius);

int main() 
{
  float celsius, fahr;
  int lower, upper, step;

  printf("%2c%7c\n", 'C', 'F');
  printf("%3s%7s\n", "---", "---");

  lower = 0;
  upper = 100;
  step = 10;

  celsius = lower;

  while(celsius <= upper) {
    fahr = convertToFahrenheit(celsius);
    
    printf("%3.0f %6.0f\n", celsius, fahr);

    celsius += step;
  }
}

int convertToFahrenheit(int celsius)
{
  return ((9.0/5.0) * celsius) + 32.0;
}
