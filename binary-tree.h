/* copied from The C programming Langage 2nd Edition */
#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdio.h>

typedef struct tnode{   /* the tree node */
  char *word;   /* points to the text */
  int count;    /* number of occurrences */
  struct tnode *left;   /* left child */
  struct tnode *right;  /* right child */
  void *extra_data; 
} tnode;

tnode *addtree(tnode *, char *, tnode **found_node);
void treeprint(tnode *p, void (*print_extra)(void*));
tnode *talloc(void);
// TODO: not requested by exercise, but free memory
//
#endif /* BINARY_TREE_H */
