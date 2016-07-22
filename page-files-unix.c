/* not using stdlib stuff yo */
/* #include <stdio.h> */
/* #include <string.h> */
/* #include <stdlib.h> */
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAXLINE 1000 /* maximum input line length */
//TODO: use getenv('LINES')
#define LINES 5
void process_file(int file_to_process);
/* call it my_ to avoid name collision with stdio function */
int my_getline(int file, char line[], int max);
void insert_page(int current_page);

/* page files */
int main(int argc, char *argv[])
{

  int current_file;
  // TODO: don't really need the switch, since this program doesn't have a mandatory param
  switch (argc) {
    case 1:
      process_file(STDIN_FILENO);
      break;
    default:
      for(int i = 1; i < argc; i++) {
        write(STDOUT_FILENO, "File: ", 6);
        //TODO: arbitrary max filename display make macro
        //TODO: this doesn't work if the file name is too short
        write(STDOUT_FILENO, argv[i], 10);
        write(STDOUT_FILENO, "\n____\n", 6);

        current_file = open(argv[i], O_RDONLY, 0);

        if (current_file == -1) {
          write(STDERR_FILENO, "Can't open file: ",  17);
          //TODO: arbitrary max filename display make macro
          write(STDERR_FILENO, argv[i],  10);
          write(STDOUT_FILENO, "\n", 1);
          /* not using since we aren't including stdlib */
          /* exit(-1); */
          return -1;
        }
        process_file(current_file);
      }
      break;
  }
}

void process_file(int file_to_search)
{
  int current_page = 0,
      current_line = 0,
      last_page_added_for_line = 0;
  char line[MAXLINE];
  int chars_read;

  // start each file on a new page
  insert_page(current_page);

  /* slight modification, end the loop for an empty line */
  while((chars_read = my_getline(file_to_search, line, MAXLINE)) > 0
      //TODO: shouldn't need this, ugly
      && line[0] != '\n') {
    write(STDOUT_FILENO, line, chars_read);
    if(++current_line % LINES == 0) {
      insert_page(++current_page);
      last_page_added_for_line = current_line;
    }
  }

  // if we haven't added a page for the last set of lines
  // then we need to add one last page.
  if (last_page_added_for_line != current_line){
    insert_page(++current_page);
  }
}

/* my_getline:get line into s, return length */
int my_getline(int file, char s[], int lim)
{
  int i = 0;

  while(--lim > 0
      && read(file, s, 1) > 0
      && ++i
      && *s++ != '\n') {
  }

  *s = '\0';

  return i;
}

void insert_page(int current_page)
{
  // if we are at the end of a page, add pg number
  if (current_page > 0) {
    //TODO: form feeds don'tseem to work, for now just emit this
    /* printf("---------%d---------\n\n", current_page); */
    // TODO: want to eliminate all stdio stuff for now, re-do this with sprintf after that so we get page numbers
    write(STDOUT_FILENO, "------------------\n\n", 20);
  }
  current_page++;
}
