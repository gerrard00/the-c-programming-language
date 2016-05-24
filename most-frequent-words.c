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
bool isnoise(const char *test_word);

//TODO: ignore case.
//TODO: some blank lines at the end, only eliminated by noise filter

typedef struct tlinked_node{   /* the tree node */
  struct tnode *simple_node;  /* this node */
  struct tlinked_node *next;  /* next node */
} tlinked_node;

tlinked_node *add_to_frequency_list(tlinked_node *current_list, tnode *new_node);

int main()
{
  char word[MAXWORD];
  int line_number = 1;
  tlinked_node *frequency_list = NULL;
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
  }

  /* treeprint(root, NULL); */
  frequency_list = add_to_frequency_list(frequency_list, root);

  while(frequency_list != NULL && frequency_list->simple_node->count > 1) {
    printf("* %d %s\n",
        frequency_list->simple_node->count,
        frequency_list->simple_node->word);

    frequency_list = frequency_list->next;
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

//TODO: should I just send in a pointer to a pointer to the list?
tlinked_node *add_to_frequency_list(tlinked_node *current_list, tnode *new_node)
{
  tlinked_node *new_linked_node = (tlinked_node *)malloc(sizeof(tlinked_node));
  tlinked_node *result;
  tlinked_node *linked_node_to_test;

  new_linked_node->simple_node = new_node;

  if (current_list == NULL) {
    result = new_linked_node;
  } else if (new_linked_node->simple_node->count > current_list->simple_node->count) {
    result = new_linked_node;
    new_linked_node->next = current_list;
  } else {
    //TODO: loop and add our node in it's rightful place
    //TODO: loop through the list until we find a node w/ a count less than ours
    //TODO: ...or a node with no next node
    result = linked_node_to_test = current_list;

    while(linked_node_to_test->next != NULL
        && linked_node_to_test->next->simple_node->count > new_node->count) {

      linked_node_to_test = linked_node_to_test->next;
    }

    // point our new node to the node that has a lower count than it (or null)
    new_linked_node->next = linked_node_to_test->next;
    linked_node_to_test->next = new_linked_node;
  }

  if (new_node->left != NULL) {
    result = add_to_frequency_list(result, new_node->left);
  }

  if (new_node->right != NULL) {
    result = add_to_frequency_list(result, new_node->right);
  }

  return result;
}
