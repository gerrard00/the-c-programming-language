#include <stdio.h>
#include "table-lookup.h"

int main()
{
  printf("before:\n\n");
  install("gerrard", "anthony");
  install("sarah", "kearns");
  install("nancy", "bernadette");
  printtable();

  printf("after:\n\n");
  undef("gerrard");
  printtable();
}
