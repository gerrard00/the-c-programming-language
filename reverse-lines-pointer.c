#include <stdio.h>

#define MAXLINE 1000 /* maximum input line size */

int my_getline(char *line, int maxline);
void reverse(char *s, int length);

/* print lines longer tan TARGET_LENGTH */
int main() 
{
  int len;    /* current line length */
  char line[MAXLINE];   /* current input line */

  while((len = my_getline(line, MAXLINE)) != EOF && len > 0) {
    reverse(line, len);
    printf("%s\n", line);
  }

  printf("\n");

  return 0;
}

/* my_getline: read a line into s, return length */
/* or return EOF if EOF received */
/* my_getline:get line into s, return length */
int my_getline(char *s, int lim)
{
	int c, i;

	i=0;
	while(--lim > 0 && (c=getchar()) != EOF && c != '\n') {
	  *s++ = c;
    i++;
	}
	if(c =='\n' )
		*s++ = c;
	*s = '\0';
	return i;
}

void reverse(char *s, int length)
{
  int end = length - 1;
  char *t = (s + end);
  char temp;

  while(t - s > 0) {
    printf("shit %ld\n", t - s);
    temp = *t;
    *t = *s;
    *s = temp;
    t--;
    s++;
  }
}

