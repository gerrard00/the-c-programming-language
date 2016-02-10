#include <stdio.h>

#define MAXLINE 1000

int my_getline(char s[], int lim);

int main() 
{
  char s[MAXLINE];
 
  while(my_getline(s, MAXLINE)) {
    printf("->%s\n", s);
  }
}

/* my_getline:get line into s, return length */
int my_getline(char *s, int lim)
{
	int c, i;

	i=0;
	while(--lim > 0 && (c=getchar()) != EOF && c != '\n') {
	  *s++ = c;
	}
	if(c =='\n' )
		*s++ = c;
	*s = '\0';
	return i;
}
