#include <stdio.h>
#include "my_malloc.h"
#include <stdlib.h>


void test_malloc(void);
void test_calloc(void);
void dump(char *, int);

int main()
{
  test_calloc();
}

void test_malloc(void)
{
  char *p1 = (char *)my_malloc(100);
  char *p2 = (char *)my_malloc(2000);
  char *p3 = (char *)my_malloc(30000);
  char *p4 = (char *)my_malloc(40);

  sprintf(p1, "bang I wrote this!\n");
  sprintf(p2, "I wrote this too. It's a little bit longer.\n");
  sprintf(p3, "Supershort");
  sprintf(p4, "This is some data that I want to add.");

  printf("The first string from our buffer (%p):\n\n%s\n\n", p1, p1);
  printf("The second string from our buffer (%p):\n\n%s\n\n", p2, p2);
  printf("The third string from our buffer (%p):\n\n%s\n\n", p3, p3);
  printf("The fourth string from our buffer (%p):\n\n%s\n\n", p4, p4);

  printf("pl - p2 = %ld\n", p1 - p2);
  printf("p1 - p3 = %ld\n", p1 - p3);
  printf("p1 - p4 = %ld\n", p1 - p4);

  my_free(p1);
  my_free(p2);
  my_free(p3);
}

void test_calloc(void)
{
  /* don't use this guy, just tracking the address */
  void *trackingPtr;

  printf("\n\ntest calloc\n\n");

  // get a pointer and write a string to it
  char *junkPtr = (char *)my_malloc(50);
  trackingPtr = junkPtr;
  sprintf(junkPtr, "this is junk data.");
  my_free(junkPtr);

  // calling malloc for the same size buffer
  // should give us the same address and
  // the data we just wrote should still be in it
  char *numPtr1 = (char *)my_malloc(50);
  printf("From malloc\n\tpointers match? (%s)\n",
      numPtr1 == trackingPtr
        ? "true"
        : "false");
  dump((char *)numPtr1, 5);
  my_free(numPtr1);

  // we get the same address again, but since
  // we call calloc, the buffer will be zeroed out
  char *numPtr2 = (char *)my_calloc(50);
   printf("From calloc\n\tpointers match? (%s)\n",
      numPtr2 == trackingPtr
        ? "true"
        : "false");
  dump((char *)numPtr2, 5);
  my_free(numPtr2);
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
