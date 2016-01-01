#include <stdio.h>
#include <errno.h>
#include <stdbool.h>

// we support C++ style comments, which are valid C as of C99
#define SINGLE_START_FIRST '/' 
#define SINGLE_START_SECOND '/' 
#define SINGLE_END '\n' 

#define MULTI_START_FIRST '/' 
#define MULTI_START_SECOND '*' 
#define MULTI_END_FIRST '*' 
#define MULTI_END_SECOND '/' 

#define MAX_LINE_LENGTH 4096

#define STATE_NORMAL 0
#define STATE_IN_SINGLE_COMMENT 1
#define STATE_IN_MULTI_COMMENT 2

#define STATE_IN_DOUBLE_QUOTES 3
#define STATE_IN_SINGLE_QUOTES 4

#define NOT_FOUND -1

void strip_comments(FILE *fp_input, FILE *fp_output);
int check_quoted_status(char last_char, char current_char, char target_char,
    int current_status, int status_to_check_for);
void dump_buffer(char buffer[], int len, FILE *stream);
int find_last_nonwhitespace(char buffer[], int len);
bool is_whitespace(char candidate);

int main(int argc, char *argv[]) 
{
  FILE *fp_input, *fp_output;

  if (argc >= 2) {
    fp_input = fopen(argv[1], "r");

    if (fp_input == NULL) {
      printf("Error opening input file: %d\n", errno);
      return -1;
    }
  } else {
    fp_input = stdin;
  }

  if (argc >=3) {
    fp_output = fopen(argv[2], "w");

    if (fp_output == NULL) {
      printf("Error opening output file: %d\n", errno);
      return -1;
    }
  } else {
    fp_output = stdout;
  }

  strip_comments(fp_input, fp_output);

  if (fp_input != NULL) {
    fclose(fp_input);
  }

  if (fp_output != NULL) {
    fclose(fp_output);
  }
  printf("\n\nDone\n");
}

void strip_comments(FILE *fp_input, FILE *fp_output)
{
  char current_char, last_char;
  // we hold at most one line and that's how big a c line can be
  // according to the spec.
  char buffer[MAX_LINE_LENGTH];
  bool comment_just_started;
  int current_state;
  int buffer_index, last_non_whitespace_index;
  // flag that tells us we may be ending a multiline comment and might
  // generate an extra empty line
  bool might_be_empty_line;

  buffer_index = 0;
  current_state = STATE_NORMAL;
  comment_just_started  =  false;
  might_be_empty_line = false;
  last_char = '\0';

  while((current_char = fgetc(fp_input)) != EOF) {

    // handle being in a comment
    if (current_state == STATE_IN_SINGLE_COMMENT 
        || current_state == STATE_IN_MULTI_COMMENT) {

      if((current_state == STATE_IN_SINGLE_COMMENT
          && current_char == SINGLE_END)
        ||
        (current_state == STATE_IN_MULTI_COMMENT
          && (last_char == MULTI_END_FIRST
            && current_char == MULTI_END_SECOND))) {

        current_state = STATE_NORMAL;
        last_char = '\0';
        // we may have just ended a multiline comment on a line
        // that is otherwise empty
        might_be_empty_line = true;
      } else {
        last_char = current_char;
      }

      continue;
    }

    current_state = check_quoted_status(last_char, current_char, '"', 
        current_state, STATE_IN_DOUBLE_QUOTES);

    current_state = check_quoted_status(last_char, current_char, '\'', 
        current_state, STATE_IN_SINGLE_QUOTES);

    // are we in a possibly empty line?
    if (might_be_empty_line) {
      if (!is_whitespace(current_char)) {
        might_be_empty_line = false;
        // go ahead and process this char normally
      } else if(current_char == '\n') {
        // we can ignore everything in the buffer
        buffer_index = 0;
        last_char = '\0';
        // turn off our warning flag
        might_be_empty_line = false;
        continue;
      }
    }

    // process the char normally.
    
    //has a comment started?
    if (current_state == STATE_NORMAL 
      && last_char == SINGLE_START_FIRST
      && current_char == SINGLE_START_SECOND) {
      
      comment_just_started = true;
      current_state = STATE_IN_SINGLE_COMMENT;
    } else if (current_state == STATE_NORMAL 
        && last_char == MULTI_START_FIRST 
        && current_char == MULTI_START_SECOND) {

      comment_just_started = true;
      current_state = STATE_IN_MULTI_COMMENT;
    }

    if (comment_just_started) {
      // find the last non-whitespace char on this line
      last_non_whitespace_index = 
        find_last_nonwhitespace(buffer, buffer_index - 2);

      if (last_non_whitespace_index != NOT_FOUND) {
        // If there was a non-whitespace char on this line,
        // dump everything on the line up to and including
        // that character. Add linefeed to the end
        // of the buffer.
        last_non_whitespace_index++;
        buffer[last_non_whitespace_index] = '\n';

        dump_buffer(buffer, last_non_whitespace_index + 1, fp_output);
      }

      buffer_index = 0;
      comment_just_started = false;
    } else if(current_char == '\n' || buffer_index == MAX_LINE_LENGTH) {
      buffer[buffer_index] = current_char;
      dump_buffer(buffer, buffer_index + 1, fp_output);  
      buffer_index = 0;
    } else {
      buffer[buffer_index++] = current_char;
      last_char = current_char;
    }
  }

  dump_buffer(buffer, buffer_index, fp_output);
}

int check_quoted_status(char last_char, char current_char, char target_char,
    int current_state, int state_to_check_for) {

  if ((current_state == STATE_NORMAL || current_state == state_to_check_for)
      && (current_char == target_char && last_char != '\\')) {

    return (current_state == state_to_check_for)
      ? STATE_NORMAL : state_to_check_for;
  }

  return current_state;
}

bool is_whitespace(char candidate)
{
  return candidate == ' ' 
        || candidate == '\t' 
        || candidate == '\n';
}

int find_last_nonwhitespace(char buffer[], int len)
{
  int i;

  i = len;
  while(i >= 0) {
    // see if the current char is whitespace
    if (!is_whitespace(buffer[i])) {
      return i;
    }
    i--;
  }

  return NOT_FOUND;
}

void dump_buffer(char buffer[], int len, FILE *stream) 
{
  int i;
  for(i = 0; i < len; i++) {
    fputc(buffer[i], stream);
  }
}
