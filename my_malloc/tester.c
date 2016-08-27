#include <stdio.h>
#include "my_malloc.h"

void dump(char *, int);

int main()
{
  char *p1 = (char *)my_malloc(1000);
  char *p2 = (char *)my_malloc(100);
  char *p3 = (char *)my_malloc(100);
  char *p4 = (char *)my_malloc(100);

  sprintf(p1, "bang I wrote this!\n");
  sprintf(p2, "I wrote this too. It's a little bit longer.\n");
  sprintf(p3, "Supershort");
  sprintf(p4, "X");

  printf("The first string from our buffer (%p):\n\n%s\n\n", p1, p1);
  printf("The second string from our buffer (%p):\n\n%s\n\n", p2, p2);
  printf("The third string from our buffer (%p):\n\n%s\n\n", p3, p3);
  printf("The fourth string from our buffer (%p):\n\n%s\n\n", p4, p4);

  printf("pl - p2 = %ld\n", p1 - p2);
  printf("p1 - p3 = %ld\n", p1 - p3);
  printf("p1 - p4 = %ld\n", p1 - p4);

  dump((char *)p1, 12);

  my_free(p1);
  my_free(p2);
  my_free(p3);
}

void dump(char *ptr, int num)
{
  for(int i = 0; i < num; i++) {
    printf("%d\t", *(ptr + i));

    if (i && (i +1) % 4 == 0) {
      printf("\n");
    }

  }

  printf("\n");
}
