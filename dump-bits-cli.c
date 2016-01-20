#include <stdio.h>
#include <stdlib.h>
#include "dump-bits.h"

int main(int argc, char *argv[]) 
{
  if(argc == 2) {
    int user_input = atoi(argv[1]);
    dump_bits(user_input);
  } else {
    for(int i = 0; i < 128; i++) {
      dump_bits(i);
    }
  }

  return 0;
}
