#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1000 /* maximum input line length */
//TODO: use getenv('LINES')
#define LINES 5
void process_file(FILE *file_to_process);
/* call it my_ to avoid name collision with stdio function */
int my_getline(FILE *file, char line[], int max);
void insert_page(int current_page);

/* page files */
int main(int argc, char *argv[])
{

  FILE *current_file;
  // TODO: don't really need the switch, since this program doesn't have a mandatory param
  switch (argc) {
    case 1:
      process_file(stdin);
      break;
    default:
      for(int i = 1; i < argc; i++) {
        printf("File: %s\n-----\n", argv[i]);
        current_file = fopen(argv[i], "r");

        if (current_file == NULL) {
          fprintf(stderr, "Can't open file %s\n", argv[i]);
          exit(-1);
        }
        process_file(current_file);
        //TODO: this no worky
        printf("\f");
      }
      break;
  }
}

void process_file(FILE *file_to_search)
{
  int current_page = 0,
      current_line = 0,
      last_page_added_for_line = 0;
  char line[MAXLINE];

  // start each file on a new page
  insert_page(current_page);

  /* slight modification, end the loop for an empty line */
  while(my_getline(file_to_search, line, MAXLINE) > 0 && line[0] != '\n') {
    printf("%s", line);
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
int my_getline(FILE *file, char s[], int lim)
{
  int c, i;

  i=0;
  while(--lim > 0 && (c=getc(file)) != EOF && c != '\n') {
    s[i++] = c;
  }
  if(c =='\n' )
    s[i++] = c;
  s[i]='\0';
  return i;
}

void insert_page(int current_page)
{
  // if we are at the end of a page, add pg number
  if (current_page > 0) {
    //TODO: form feeds don'tseem to work, for now just emit this
    printf("---------%d---------\n\n", current_page);
  }
  current_page++;
}
