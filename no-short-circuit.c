#include <stdio.h>

int main() 
{
  int lim = 8;
  int i = 0;
  int realLength = 0;
  char s[lim];
  char c = '\0';

  printf("Enter some characters:");

  /* for(i = 0; i < lim -1 && (c=getchar())  != '\n' && c != EOF; ++i, realLength++ */
/* ) { */
  /*       s[i] = c; */
  /* } */

  while (i < lim -1) {
    c = getchar();

    if (c == '\n') {
      printf("need to leave");
      break;
    }

    if (c == EOF) {
      printf("need to leave");
      break;
    }

    s[i] = c;
    i++;
    realLength++;
  }

  printf("word: \"");
  for(i = 0; i < realLength; i++) {
    printf("%c", s[i]);
  }
  printf("\"\n");

  printf("Done!\n");
}
