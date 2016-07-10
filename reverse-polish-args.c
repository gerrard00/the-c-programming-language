#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <math.h>
#include <string.h>
#include <stdbool.h>
// needed for isdigit
#include <ctype.h>

#define MAXLINE 1000   /* max size of line */
#define MAXOP 100   /* max size of operand or operator */
#define NUMBER '0'  /* signal that a number was found */
#define GET_VARIABLE '$'  /* signal that a get var was found */
#define COMMAND '@'  /* signal that a command was found */

int getop_type(char *op);
void push(double);
double pop(void);
double peek(void);
void dupe(void);
void clear(void);
void swap(void);
void dump(void);
void handle_library_function(char s[]);
bool is_variable_name(char c);
void set_last_variable(float val);
void set_variable(char variable_name, float val);
float get_variable(char variable_name);

/* reverse Polish calculator */
int main(int argc, char *argv[])
{
  int type;
  double op2;
  char *current_op;

  if (argc == 1) {
    printf("usage: reverse-polish-args expression\n");
    return -1;
  }

  while (--argc > 0) {
    current_op = *++argv;
    type = getop_type(current_op);
    /* printf("type: %c\n", type); */
    /* printf("string: %s\n", s); */

    switch (type) {
      case NUMBER:
        push(atof(current_op));
        break;
      case '+':
        push(pop() + pop());
        break;
      case '*':
        push(pop() * pop());
        break;
      case '-':
        op2 = pop();
        push(pop() - op2);
        break;
      case '/':
        op2 = pop();
        if (op2 != 0.0) {
          push(pop() / op2);
        } else {
          printf("error: zero divisor\n");
          return -1;
        }
        break;
      case '%':
        op2 = pop();
        if (op2 != 0.0) {
          push((int)pop() % (int)op2);
        } else {
          printf("error: zero divisor\n");
          return -1;
        }
        break;
      case 'p':
        printf("%f\n", peek());
        break;
      case 'd':
        dupe();
        printf("%f\n", peek());
        break;
      case 'c':
        clear();
        break;
      case 's':
        swap();
        printf("%f\n", peek());
        break;
      case 'z':
        dump();
        break;
      case COMMAND:
        //TODO: use a const return value from getop_type instead of hardcoding at sign?
        handle_library_function(current_op);
        break;
      case GET_VARIABLE:
        push(get_variable(*(current_op + 1)));
        break;
      default:
        if (is_variable_name(type)) {
          set_variable(type, pop());
        } else {
          printf("error: unknown command %s\n", current_op);
          return -1;
        }
        break;
    }
  }

  printf("------------------\n");
  printf("\t%f\n", peek());
  printf("\n");

  return 0;
}

#define MAXVAL 100 /* maximum depth of val stack */

int sp = 0; /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f)
{
  if (sp < MAXVAL) {
    val[sp++] = f;
  } else {
    printf("error: stack full, can't push %g\n", f);
  }
}

/* pop: pop and return top value from stack */
double pop(void)
{
  if (sp > 0) {
    return val[--sp];
  } else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

/* peek: peek at top value from stack, without popping */
double peek(void)
{
  if (sp > 0) {
    return val[sp - 1];
  } else {
    /* don't show an error, we sometimes peek at an empty stack */
    /* printf("error: stack empty\n"); */
    return 0.0;
  }
}

/* dupe: dupe the top value from stack */
void dupe(void)
{
  if (sp > 0) {
    sp++;
    val[sp - 1] = val[sp - 2];
  } else {
    printf("error: stack empty\n");
  }
}

/* clear: clear the stack */
void clear(void)
{
  sp = 0;
}

/* swap: swap the top two items on the stack */
void swap(void)
{
  float temp = val[sp - 1];
  val[sp - 1] = val[sp - 2];
  val[sp - 2] = temp;
}

/* dump: dump the top two items on the stack */
void dump(void)
{
  printf("<<<<dump>>>\n");
  for(int i = 0; i < sp; i++) {
    printf("(%3d) %f\n", i, val[i]);
  }
  printf("<<<<\\dump>>>\n");
}


/* getop_type: get type of operator or numeric operand */
int getop_type(char *op)
{
  int c;
  int result;

  c = *op;

  if (isdigit(c) || c == '.' || c == '-') {
    result = NUMBER;
  } else {
    result = c;
  }

  /* printf("c now int: %d\n", c); */
  /* printf("c now char: %c\n", c); */

  /* if the first digit is a dash and there are no other chars,
   * it's an operator and not a number. */
  if (result == NUMBER && c == '-' && *(op + 1) == '\0') {
    // what we have here is a subtraction operator
    return c;
  }

  /* printf("string: <<--%s-->>\n", s); */
  /* printf("result int: %d\n", result); */
  /* printf("result char: %c\n", result); */

  return result;
}

void handle_library_function(char s[])
{
  float op2;

  if (strcmp(s, "@sin") == 0) {
    push(sin(pop()));
  } else if (strcmp(s, "@exp") == 0) {
    push(exp(pop()));
   } else if (strcmp(s, "@pow") == 0) {
    op2 = pop();
    push(pow(pop(), op2));
  } else {
    printf("error: unknown library command %s\n", s);
  }
}

// create a global to hold our variable values, initialized to zeros
#define NUMBER_OF_VARIABLES 26
#define VARIABLE_NOT_FOUND -1
#define LAST_VARIABLE_CHAR '!'
float variables[NUMBER_OF_VARIABLES] = {0};
float last_variable = 0;

bool is_variable_name(char c)
{
  return (c == LAST_VARIABLE_CHAR
      || (c >= 'A' && c <= 'Z'));
}

int get_letter_variable_index(char variable_name)
{
  if (variable_name >= 0 || variable_name < NUMBER_OF_VARIABLES) {
    return variable_name - 'A';
  } else {
    printf("Unknown variable %c\n", variable_name);
    return VARIABLE_NOT_FOUND;
  }
}

void set_variable(char variable_name, float val)
{
  int variable_index;

  if (variable_name == LAST_VARIABLE_CHAR) {
    printf("$! variable cannot be set directly.\n");
    return;
  }

  if ((variable_index = get_letter_variable_index(variable_name))
      != VARIABLE_NOT_FOUND) {
    variables[variable_index] = val;
  } else {
    printf("Unknown variable %c\n", variable_name);
  }
}

void set_last_variable(float val)
{
  last_variable = val;
}

float get_variable(char variable_name)
{
  int variable_index;

  if (variable_name == LAST_VARIABLE_CHAR) {
    return last_variable;
  }

  if ((variable_index = get_letter_variable_index(variable_name))
      != VARIABLE_NOT_FOUND) {
    return variables[variable_index];
  }
  return 0.0;
}

