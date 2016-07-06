#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

/* minscanf: minimal scanf with variable argument list */
void minscanf(char *fmt, ...)
{
  va_list ap;
  char *p, *sval, *cval;
  int *ival;
  float *fval;
  char temp_c;

  va_start(ap, fmt); /* make ap point to 1st unnamed arg */
  for (p = fmt; *p; p++) {
    if (*p != '%') {
      /* putchar(*p); */
      continue;
    }

    ++p;

    // process format specifier
    switch (*p) {
      case 'd':
        ival = va_arg(ap, int*);
        scanf("%d", ival);
        break;
      case 'f':
        fval = va_arg(ap, float*);
        scanf("%f", fval);
        break;
      // add another type
      case 'c':
        cval = va_arg(ap, char*);
        scanf("%c", cval);
        break;
      case 's':
        sval = va_arg(ap, char *);
        scanf("%s", sval);
        // TODO: quick hack to skip space
        temp_c = getchar();
        if (temp_c == EOF) {
          ungetc(temp_c, stdin);
        }
       break;
      default:
        putchar(*p);
        break;
    }
  }
  va_end(ap);   /* clean up when done */
}

int main()
{
/* Gerrard A Lindsay 38 217.8 */
  char fname[100], lname[100];
  char initial = '\0';
  int age = 0;
  float weight = 0;

  minscanf("%s %c %s %d %f", 
      fname, &initial, lname, &age, &weight);

  printf("name: %s %s\n", fname, lname);
  printf("initial: %c\n", initial);
  printf("age: %d\n", age);
  printf("weight: %f\n", weight);

  printf("\nDone!\n");
}
