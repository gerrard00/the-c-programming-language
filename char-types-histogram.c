#include <stdio.h>

void display_bar(int length) {
  int j;

  for (j = 0; j < length; ++j) {
    printf("*");
  }
  printf("\n");
}

/* count digits, white spce, others */
int main() 
{
  int c, i;
  int nspace, ntab, nnewline, nother;
  int ndigit[10], nloweralpha[26];

  nspace = ntab = nnewline = nother = 0;
  for(i = 0; i < 10; ++i) {
    ndigit[i] = 0;
  }
  for(i = 0; i < 26; ++i) {
    nloweralpha[i] = 0;
  }
  while((c = getchar()) != EOF) {
    if (c >= '0' & c <='9') {
      ++ndigit[c - '0'];
    } else if (c >= 'a' & c <='z') {
      ++nloweralpha[c - 'a'];
    } else if (c == ' ') {
      ++nspace;
    } else if (c == '\n') {
      ++nnewline;
    } else if (c == '\t') {
      ++ntab;
    } else {
      ++nother;
    }
  }

  for (i = 0; i < 10; ++i) {
    printf("%4d|", i);
    display_bar(ndigit[i]);
  }

  for (i = 0; i < 26; ++i) {
    printf("%4c|", 'a' + i);
    display_bar(nloweralpha[i]);
  }
  printf("<sp>|");
  display_bar(nspace);
  printf("  \\n|");
  display_bar(nnewline);
  printf("  \\t|");
  display_bar(ntab);
}
