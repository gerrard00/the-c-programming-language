#include <stdio.h>
#include <string.h>
#include "dcl-common.h"

int main() /* convert declaratin to words */
{
  while(gettoken() != EOF) { /* 1st token on line */
    strcpy(datatype, token); /* is the datatype */
    out[0] = '\0';
    /* parse rest of line */
    if (!dcl() || tokentype != '\n') {
      printf("\n*syntax error*\n\n");
      reset();
    } else {
      printf("%s: %s %s\n\n", name, out, datatype);
    }
  }

  return 0;
}
