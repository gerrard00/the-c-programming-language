#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAXLINELENGTH 1000
/* compare-files: compare two files and print the first line where they differ */
int main(int argc, char *argv[])
{
  char *filename1, *filename2;
  FILE *file1, *file2;
  bool read_line_from_file1, read_line_from_file2;
  char line1[MAXLINELENGTH], line2[MAXLINELENGTH];
  int current_line_number = 0;

  if (argc < 2) {
    printf("usage:\n\tcompare-files file1 file2\n");
    return 1;
  }

  filename1 = argv[1];
  filename2 = argv[2];

  if((file1 = fopen(filename1, "r")) == NULL) {
    printf("unable to open file %s for reading.\n", filename1);
  }

  if((file2 = fopen(filename2, "r")) == NULL) {
    printf("unable to open file %s for reading.\n", filename2);
  }

  while((read_line_from_file1 = (fgets(line1, MAXLINELENGTH, file1) != NULL))
      // no shortcircuit or, we want to check both files every time
      | (read_line_from_file2 = (fgets(line2, MAXLINELENGTH, file2) != NULL))) {

    current_line_number++;

    if (!read_line_from_file1
        || !read_line_from_file2
        || strcmp(line1, line2) != 0) {
      break;
    }
  }

  // both null: looks like we have a match
  if (!read_line_from_file1 && !read_line_from_file2) {
    printf("Files are identical.\n");
  // first one null, second one not: first file is shorter
  } else if (!read_line_from_file1) {
    printf("File 1 %s is shorter at %d lines long.\n",
        filename1, current_line_number);
  // second one null, second one not: first file is shorter
  } else if (!read_line_from_file2) {
    printf("File 2 %s is shorter at %d lines long.\n",
        filename2, current_line_number);
  // the files don't match
  } else {
    printf("Files differ starting on line %d:\n \
      \tfile1: %s\n \
      \tfile2: %s\n", current_line_number, line1, line2);
  }
  return 0;
}
