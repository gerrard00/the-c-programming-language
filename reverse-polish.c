#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <math.h>
#include <string.h>
#include <stdbool.h>

#define MAXOP 100   /* max size of operand or operator */
#define NUMBER '0'  /* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);
double peek(void);
void dupe(void);
void clear(void);
void swap(void);
void dump(void);
void get_full_op(char s[]);
void handle_library_function(char s[]);
bool is_variable_name(char c);
void set_last_variable(float val);
void set_variable(char variable_name, float val);
float get_variable(void);

/* reverse Polish calculator */
int main()
{
  int type;
  double op2;
  char s[MAXOP];

  while ((type = getop(s)) != EOF) {
    switch (type) {
      case NUMBER:
        push(atof(s));
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
        }
        break;
      case '%':
        op2 = pop();
        push((int)pop() % (int)op2);
        break;
      case '\n':
        printf("--------------\n");
        printf("\t%f\n", peek());
        set_last_variable(peek());
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
        printf("%f\n", 0.0);
        break;
      case 's':
        swap();
        printf("%f\n", peek());
        break;
      case 'z':
        dump();
        break;
      case '@':
        handle_library_function(s);
        break;
      case '$':
        push(get_variable());
        break;
      default:
        if (is_variable_name(type)) {
          set_variable(type, pop());
        } else {
          printf("error: unknown command %s\n", s);
        }
        break;
    }
  }
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

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next operator or numeric operand */
int getop(char s[])
{
  int i, c, next_c;

  while((s[0] = c  = getch()) == ' ' || c == '\t') {
    ;
  }
  s[1] = '\0';
  if (!isdigit(c) && c != '.' && c != '-') {
    return c; /* not a number */
  }
  i = 0;
  /* collect negative sign, if present */
  if (c == '-') {
    /* could be a subtract operator or a negative sign */
    next_c = getch();

    if (!isdigit(next_c)) {
      /* it's a subtract operator */
      ungetch(next_c);
      return c;
    }

    /* it's a negative sign */
    c = s[++i] = next_c;
  }
  /* collect integer part */
  if(isdigit(c)) {
    while (isdigit(s[++i] = c = getch())) {
      ;
    }
  }
  /* collect fraction part */
  if (c == '.')  {
    while(isdigit(s[++i] = c = getch())) {
      ;
    }
  }
  s[i] = '\0';
  if(c != EOF) {
    ungetch(c);
  }
  return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0; /* next free position in buf */

/* get a (possibly pushed back) character */
int getch(void)
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void ungetch(int c)
{
  if (bufp >= BUFSIZE) {
    printf("ungetch: too many characters\n");
  } else {
    buf[bufp++] = c;
  }
}

void handle_library_function(char s[])
{
  float op2;
  get_full_op(s);

  if (strcmp(s, "sin") == 0) {
    push(sin(pop()));
  } else if (strcmp(s, "exp") == 0) {
    push(exp(pop()));
   } else if (strcmp(s, "pow") == 0) {
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
      || (c >= 'a' && c <= 'z'));
}

int get_letter_variable_index(char variable_name)
{
  if (variable_name >= 0 || variable_name < NUMBER_OF_VARIABLES) {
    return variable_name - '0';
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
  }
}

void set_last_variable(float val)
{
  last_variable = val;
}

float get_variable()
{
  char variable_name = getch();
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

void get_full_op(char s[])
{
  int i = 0;
  char c;
  while((s[i++] = c  = getch()) != ' '
      &&  c != '\t'
      && c != '\n'
      && c != '\0'
      && c != EOF) {
    ;
  }
  s[i - 1] = '\0';

  if (c != EOF) {
    ungetch(c);
  }
}

