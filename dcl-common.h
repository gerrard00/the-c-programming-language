#ifndef DCL_COMMON
#define DCL_COMMON

#include <stdbool.h>
#define MAXTOKEN 100

enum { UNKNOWN, NAME, PARENS, BRACKETS};

bool dcl(void) ;
bool dirdcl (void);
void reset(void);
int gettoken(void);

int tokentype; /*type of last token*/
char token[MAXTOKEN]; /*last token string*/
char name [MAXTOKEN]; /*identifier name*/
char datatype[MAXTOKEN]; /*data type = char, int, etc.*/
char out [1000]; /*output string*/

#endif
