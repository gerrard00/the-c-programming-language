#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef int modifier(int);
void print_upper(modifier);

int main(__attribute__((unused)) int argc, char *argv[])
{
  if(strstr(argv[0], "lower") != NULL) {
    print_upper(tolower);
  } else if(strstr(argv[0], "upper") != NULL) {
    print_upper(toupper);
  } else {
    printf("Not sure which case to target, invoked as %s\n", argv[0]);
  }
}

void print_upper(modifier m)
{
  char c;

  while((c = getchar()) != EOF) {
    putchar(m(c));
  }
  return;
}

