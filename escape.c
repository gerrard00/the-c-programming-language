#include <stdio.h>
#include <string.h>
#include <assert.h>

/*
Exercise 3-2. Write a function escape(s, t) that converts characters like
newline and tab into visible escape sequences like \n and \t as it copies the
string to s. Use a switch. Write a function for the other direction as well,
converting escape sequences into the real characters.
*/
#define MAX_LINE 1000

void escape(char s[], char t[])
{
  int i, j;
  int len = strlen(t);

  for(i = j = 0; i < len; i++, j++) {
    switch(t[i]) {
      case '\t':
        s[j] =  '\\';
        s[++j] = 't';
        break;
      case '\n':
        s[j] =  '\\';
        s[++j] = 'n';
        break;
      default:
        s[j] = t[i];
        break;
    }
  }
  s[j] = '\0';
}

void unescape(char s[], char t[])
{
  int i, j;
  int len = strlen(t);

  for(i = j = 0; i < len; i++, j++) {
    switch(t[i]) {
      case '\\':
        if (i < len - 1) {
          i++;
          switch(t[i]) {
            case 't':
              s[j] = '\t';
              break;
            case 'n':
              s[j] = '\n';
              break;
            default:
              s[j] = t[i];
              break;
          }
        } else {
          assert(0);
        }

        break;
      default:
        s[j] = t[i];
        break;
    }
  }
  s[j] = '\0';
}

int main() 
{
  char t[] = "This is line one.\nThis is line two\twith a tab.\nLine three ends with a slash";
  char s[MAX_LINE];
  char us[MAX_LINE];

  printf("t:\n%s\n", t);
  printf("\n");
  escape(s, t);
  printf("s:\n%s\n", s);
  printf("\n");
  unescape(us, s);
  printf("us:\n%s\n", us);
}
