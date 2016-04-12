#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "dcl-common.h"

int real_gettoken(void) /*return next token*/
{
  int c;
  char *p= token;

  while((c = getc(stdin)) ==  ' ' || c == '\t') {
    ;
  }

  if (c == '(') {
    if((c = getc(stdin)) == ')') {
      debug_print("matching parens, returning PARENS\n");
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

void dump_token_info(int token_type)
{
  switch(token_type) {
    case UNKNOWN:
      debug_print("UNKNOWN\n");
      break;
    case NAME:
      debug_print("NAME:%s\n", token);
      break;
    case PARENS:
      debug_print("PARENS\n");
      break;
    case BRACKETS:
      debug_print("BRACKETS\n");
      break;
    case EOF:
      debug_print("EOF\n");
      break;
    default:
      debug_print("%c (ascii: %d)\n", token_type, token_type);
      break;
  }
}

int gettoken(void) /*return next token*/
{
  int result = real_gettoken();
  debug_print("\tgettoken: ");
  dump_token_info(result);

  return result;
}

/*dirdcl:parse a direct declarator*/
bool dirdcl(void)
{
  char function_argument_datatype[MAXTOKEN]; /*data type = char, int, etc.*/
  debug_print("dirdcl called\n");
  debug_print("\tin function arguments? %d \n", in_function_arguments);
  int type;

  debug_print("dirdcl token type before starting: %d\n", tokentype);
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
    debug_print("dircl bad type: ");
    dump_token_info(tokentype);
    printf("error:expected name or (dcl)\n");
    return false;
  }

  debug_print("about to start dirdcl loop\n");
  while((type=gettoken()) == PARENS || type == '(' || type == BRACKETS) {
    debug_print("dirdcl type in loop: %d\n", type);
    if (type == PARENS) {
      strcat(out, " function returning");
    } else if (type == '(') {
      in_function_arguments = true;
      strcat(out, " function taking (");
      while((type = gettoken()) != ')' && type != '\n' && type != EOF) {
        strcpy(function_argument_datatype, token);
        debug_print("\t------------->dircl loop: ");
        dump_token_info(type);
        if (type != NAME) {
          debug_print("func args not name, continue:");
          dump_token_info(type);
          continue;
        }

        // Call dcl to skip past the name.
        // Note that we don't actually include 
        // the name in the output.
        dcl();

        debug_print("type after dcl in func args:");
        dump_token_info(tokentype);
        strcat(out, " ");
        strcat(out, function_argument_datatype);

        if (tokentype != ',') {
          debug_print("Expected comma, but got:");
          dump_token_info(type);
          break;
        } else {
          strcat(out, ",");
        }
      }
      in_function_arguments = false;
      debug_print("Current results:\n");
      debug_print(out);
      debug_print("\n");
      if (tokentype != ')') {
        debug_print("Function args didn't end, instead saw ");
        dump_token_info(type);
        ungetc(type, stdin);
        printf("error: missing ) after function arguments.\n");
        return false;
      }

      strcat(out, " ) and returning");
    } else {
      strcat (out," array");
      strcat(out, token);
      strcat (out," of");
    }
  }
  debug_print("dirdcl type after loop: %d\n", type);

  return true;
}

/*dcl:parse a declarator*/
bool dcl(void)
{
  debug_print("dcl called\n");
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
