#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
  va_list ap;
  char *p, *sval;
  int ival;
  double dval;
  // flag related stuff
  bool processing_flags = false;
  bool always_show_sign = false;

  va_start(ap, fmt); /* make ap point to 1st unnamed arg */
  for (p = fmt; *p; p++) {
    if (*p != '%') {
      putchar(*p);
      continue;
    }

    // process flags
    ++p;
    processing_flags = true;
    while(processing_flags) {
      switch(*p) {
        case '+':
          always_show_sign = true;
          break;
        default:
          processing_flags = false;
          break;
      }

      if (!processing_flags) {
        break;
      }

      ++p;
    }

    // process format specifier
    switch (*p) {
      case 'd':
        ival = va_arg(ap, int);
        if (always_show_sign) {
          printf("%+d", ival);
        } else {
          printf("%d", ival);
        }
        break;
      case 'f':
        dval = va_arg(ap, double);
        printf("%f", dval);
        break;
      // add another type
      case 'c':
        sval = va_arg(ap, char *);
        putchar(*sval);
        break;
      case 's':
        for(sval = va_arg(ap, char *); *sval; sval++) {
          putchar(*sval);
        }
        break;
      default:
        putchar(*p);
        break;
    }
    va_end(ap);   /* clean up when done */
  }
}

/* int main(int argc, char *argv[]) */
int main()
{
  /* minprintf("i: %d f: %f s: %s\n", */
  /*   7, 4.5, "Gerrard"); */

  /* // c format */
  /* minprintf("i: %d f: %f c: %c s: %s\n", */
  /*   7, 4.5, "Bang", "Gerrard"); */

  // sign always present for int
  minprintf("d: %d +d: %+d\n", 7, 7);
  minprintf("d: %d +d: %+d\n", -7, -7);

}
