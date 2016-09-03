#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_malloc.h"

void test_malloc(void);
void test_calloc(void);
void test_malloc_too_big(void);
void test_free_invalid(void);
void test_free_non(void);
void test_bfree(void);
void dump(char *, int);

int main()
{
  printf("\n\ntesting\n\n");
  /* test_malloc(); */
  /* test_calloc(); */
  /* test_malloc_too_big(); */
  /* test_free_invalid(); */
  test_bfree();
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

void test_malloc_too_big(void)
{
  unsigned tooBigNumBytes = (unsigned) -1;
  void *ptr = my_malloc(tooBigNumBytes);

  printf("Is it null (i.e. too big a request): %s\n",
      ptr == NULL ? "true" : "false");
}

void test_free_invalid(void)
{
   /* test calling w/ NULL pointer */
  my_free(NULL);

  /* make it a long so we can easily get the size */
  /* which is long */
  long *ptr = (long *)my_malloc(1024);
  printf("real size: %ld\n", *(ptr - 1));
  *(ptr - 1) = (unsigned) -1;
  my_free(ptr);
}

void test_bfree(void)
{
  /*
   * create a string array with some digits and a target string
  */
  #define RONIN_LENGTH 100
  /* we hope to see this string in the end */
  #define EXPECTED_OUTPUT "Lone Wolf And Cub."
  /* we'll lose one header length (16 bytes) */
  /* prefix our expected output with one header length of junk */
  #define ORIGINAL_INPUT "0123456789ABCDEF" EXPECTED_OUTPUT

  /*
    the first 16 chars will be overwritten with header
    after our round trip
  */
  char ronin[RONIN_LENGTH] = ORIGINAL_INPUT;
  void *trackingPtr = &ronin;

  /*
    allocate and deallocate a buffer, to ensure
    frep is set.
  */
  void *ptr = my_malloc(1024);
  my_free(ptr);

  printf("ronin: %p\n", &ronin);
  bfree(&ronin, RONIN_LENGTH);
  char *charPtr = my_malloc(RONIN_LENGTH);
  printf("charPtr: %p\n", charPtr);
  printf("right pointer address? %s\n",
      (charPtr == trackingPtr + 16)
        ? "true"
        : "false");
  printf("dirty buffer contents: %s\n", charPtr);
  printf("got expected output in dirty buffer? %s\n",
      (strcmp(EXPECTED_OUTPUT, charPtr) == 0)
        ? "true"
        : "false");
}
