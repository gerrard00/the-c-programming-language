#ifndef DCL_COMMON
#define DCL_COMMON

#include <stdio.h>
#include <stdbool.h>
#define MAXTOKEN 100

enum { UNKNOWN, NAME, PARENS, BRACKETS};

bool dcl(void) ;
bool dirdcl (void);
void reset(void);
int gettoken(void);

int tokentype; /*type of last token*/
int previous_tokentype; /* type of token before last */
char token[MAXTOKEN]; /*last token string*/
char name [MAXTOKEN]; /*identifier name*/
char datatype[MAXTOKEN]; /*data type = char, int, etc.*/
char out [1000]; /*output string*/

//TODO: remove this debug variable
bool in_function_arguments;
#define DEBUG 0
/* http://stackoverflow.com/a/1644898/1011470 */
#define debug_print(...) \
  do { if (DEBUG) fprintf(stderr, __VA_ARGS__); } while (0)

#endif
