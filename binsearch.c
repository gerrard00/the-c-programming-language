#include <stdio.h>
#include <string.h>
#include <assert.h>

/*
Exercise 3-1. Our binary search makes two tests inside the loop, when one
wouldsuffice (at the price of more tests outside). Write a versionwith only one
test inside the loopand measure the difference in run-time.0
*/

/* binsearch:find x in v[O]<=v[1]<=•••<=v[n-1]*1 */
int their_binsearch(int x, int v[], int n)
{
  int low, high, mid;
  low=0;
  high=n - 1;
  while (low<=high) {
    mid=(low+high)/2;
    if (x<v[mid])
      high=mid - 1;
    else if (x>v[mid])
      low=mid + 1;
    else /*found match*/
      return mid;
  }
        
  return -1;/*no match*/
}

int my_binsearch(int x, int v[], int n)
{
  int low, high, mid;
  low=0;
  high=n - 1;
  while (low<=high) {
    mid=(low+high)/2;
    /* printf("mid: %d\n", mid); */
    if (x<v[mid])
      high=mid - 1;
    else 
      low=mid + 1;
  }
  
  /* printf("\tlow: %d\n", low); */
  /* printf("\tmid: %d\n", mid); */
  /* printf("\thigh: %d\n", high); */

  if (v[low] == x) {
    return low;
  } else if (v[high] == x) {
    return high;
  }
  return -1;/*no match*/
}

#define NUMBER 1000000

void test_my_binsearch(int x, int v[], int n)
{
  printf("\nTest: %d\n", x);
  int their_result = their_binsearch(x, v, n);
  printf("\tTheir result:\t%d\n", their_result);
  int my_result = my_binsearch(x, v, n);
  printf("\tResult:\t\t%d\n", my_result);
  assert(their_result == my_result);
  assert(my_result == -1 || v[their_result] == x);
}

void time_mine(int values[])
{
  their_binsearch(7500, values, NUMBER);
}

void time_theirs(int values[])
{
  my_binsearch(7500, values, NUMBER);
}

int main(int argc, char *argv[]) 
{
  int values[NUMBER];
  int timed_result;
  /* int target = (NUMBER/2) + 10; */
  /* int target = -100; */
  /* int target = NUMBER + 100; */

  for(int i = 0; i < NUMBER; i++) {
    values[i] = (i == 777)
      ? (i = i + 2)
      : i + 1;
  }
  
  /* test_my_binsearch(750, values, NUMBER); */
  /* test_my_binsearch(values[NUMBER/2] + 1000, values, NUMBER); */
  /* test_my_binsearch(1000, values, NUMBER); */
  /* printf("\nbad************\n"); */
  /* test_my_binsearch(778, values, NUMBER); */
  /* test_my_binsearch(NUMBER + 1, values, NUMBER); */
  /* test_my_binsearch(-1, values, NUMBER); */

  if (argc == 2 && strcmp("mine", argv[1]) == 0) {
    printf("mine\n");
    timed_result = my_binsearch(7500, values, NUMBER);
  } else {
    printf("theirs\n");
    timed_result = their_binsearch(7500, values, NUMBER);
  }

  printf("Timed result: %d\n", timed_result);
}
