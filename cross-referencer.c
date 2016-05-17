#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "binary-tree.h"

#define MAXWORD 100
#define MAXOCCURENCES 100

int getword(char *, int);
static tnode *root = NULL;
static tnode *current_node = NULL;
const char *noise_words[] = { "and", "it", "of", "or", "the", "to", "was" };
#define NUMBER_OF_NOISE_WORDS (int)(sizeof noise_words/sizeof noise_words[0])

//TODO: ignore case.
//TODO: some blank lines at the end, only eliminated by noise filter
//TODO: store position in line?

void add_occurrence(int line_number, int *extra_data);
void print_occurrences(void *extra_data);
bool isnoise(const char *test_word);

int main()
{
  char word[MAXWORD];
  int *current_references;
  int line_number = 1;

  //TODO: need to figure out what line we are on, current getword doesn't support that
  while (getword(word, MAXWORD) != EOF) {
    // if we got a newline, just increment our line counter
    if (word[0] == '\n') {
      line_number++;
      continue;
    }

    if (isnoise(word)) {
      continue;
    }

    root = addtree(root, word, &current_node);

    if (current_node->extra_data == NULL) {
      current_references = malloc(sizeof(int) * MAXOCCURENCES);
      *current_references = line_number;
      current_node->extra_data = current_references;
    } else {
      add_occurrence(line_number, (int*)current_node->extra_data);
    }
  }

  treeprint(root, print_occurrences);
}

//TODO: make this return a bool to indicate success?
void add_occurrence(int line_number, int *extra_data)
{
  int index = 0;

  while(index < MAXOCCURENCES
      && extra_data[index] != line_number
      && extra_data[index] != 0) {
    index++;
  }

  if (index == MAXOCCURENCES) {
    //boom
    return;
  }

  if (extra_data[index] == line_number) {
    // we already have it, no problemo
    return;
  }

  extra_data[index] = line_number;
}

void print_occurrences(void *extra_data)
{
  int *occurrences = (int*) extra_data;
  int index = 0;

  while (index < MAXOCCURENCES && occurrences[index] != 0) {
    printf("\tline: %d\n", occurrences[index++]);
  }
}

bool isnoise(const char *test_word)
{
  // hack for punctuation
  if (!isalpha(test_word[0])) {
    return true;
  }

  // noise words
  for(int index = 0; index < NUMBER_OF_NOISE_WORDS; index++) {
    if (strcmp(noise_words[index], test_word) == 0) {
      return true;
    }
  }
  return false;
}

