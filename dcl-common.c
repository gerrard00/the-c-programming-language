#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "dcl-common.h"

int gettoken(void) /*return next token*/
{
	int c;
	char *p= token;

	while((c = getc(stdin)) ==  ' ' || c == '\t') {
		;
	}

	if (c == '(') {
		if((c = getc(stdin)) == ')') {
			strcpy(token, "()");
      return tokentype = PARENS;
    } else {
      ungetc(c, stdin);
      return tokentype = '(';
    }
	} else if (c == '[') {
    for(*p++ = c; (*p++ = getchar()) != ']'; ) {
      ;
    }
    *p = '\0';
    return tokentype = BRACKETS;
  } else if (isalpha(c)) {
    for(*p++ = c; isalnum(c = getc(stdin)); ) {
      *p++ = c;
    }
    *p = '\0';
    ungetc(c, stdin);
    return tokentype = NAME;
  } else {
    return tokentype = c;
  }
}

/*dirdcl:parse a direct declarator*/
bool dirdcl(void)
{
  int type;

  if (tokentype == '(') { /* (dcl )*/
    if (!dcl()) {
      return false;
    }

    if (tokentype != ')') {
      printf("error: missing )\n");
      return false;
    }
  } else if (tokentype == NAME) { /*variable name*/
    strcpy(name, token);
  } else {
    printf("error:expected name or (dcl)\n");
    return false;
  }

  while((type=gettoken()) == PARENS || type == BRACKETS) {
    if (type == PARENS) {
      strcat(out, " function returning");
    } else {
      strcat (out," array");
      strcat(out, token);
      strcat (out," of");
    }
  }

  return true;
}

/*dcl:parse a declarator*/
bool dcl(void)
{
	int ns;

	for (ns=0; gettoken() == '*'; ) { /* count *'s */
		ns++;
	}
	if (!dirdcl()) {
    return false;
  }
	while(ns-- > 0) {
		strcat(out, " pointer to");
	}

  return true;
}

void reset(void) 
{
  char current_char;

  /* not really necessaryto clear these */
  tokentype = 0;
  name[0] = '\0';
  datatype[0] = '\0';

  // skip the rest of the line
  while ((current_char = getc(stdin)) != '\n' && current_char != EOF) {
    ;
  }
}