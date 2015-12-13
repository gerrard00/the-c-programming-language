#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP  20

/* print Fahrenheit-Celsius table
  for fahr = 0, 20, ..., 300 */
int main()
{
  int fahr;

  printf("%2c%7c\n", 'F', 'C');
  printf("%3s%7s\n", "---", "---");

  for(fahr = UPPER; fahr >= LOWER; fahr -= STEP) {
    printf("%3d %6.1f\n", fahr, (5.0/9.0) * (fahr-32));
  }
}
