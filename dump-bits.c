#include <stdio.h>
#include <stdlib.h>
#include "dump-bits.h"

/* int main(int argc, char *argv[]) */ 
/* { */
/*   if(argc == 2) { */
/*     int user_input = atoi(argv[1]); */
/*     dump_bits(user_input); */
/*   } else { */
/*     for(int i = 0; i < 128; i++) { */
/*       dump_bits(i); */
/*     } */
/*   } */

/*   return 0; */
/* } */

void dump_bits(int val)
{
  /* int mask = 1; */
  int mask = 1 << (BITS_TO_SHOW - 1);
  char output;

  for(int i = 0; i < BITS_TO_SHOW; i++) {
    output = (val & mask) ? '1' : '0';
    printf("%c", output);
    mask = mask >> 1;

    if ((i + 1) % 8 == 0) {
      printf(" ");
    }
  }

  printf("\n");
}
