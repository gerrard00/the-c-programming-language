/* copied from The C programming Langage 2nd Edition */
#include "binary-tree.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/* talloc: make a tnode */
tnode *talloc(void) 
{
  return (tnode *) malloc(sizeof(tnode));
}

/* addtree: add a node with w, at or below p */
tnode *addtree(tnode *p, char *w, tnode **found_node) 
{
  int cond;

  if(p == NULL) {   /* a new word has arrived */
    p = talloc();   /* make a new node */
    p->word = strdup(w);
    p->count = 1;
    p->left = p->right = NULL;
    *found_node = p; 
  } else if ((cond = strcmp(w, p->word)) == 0) {
    p->count++;   /* repeated word */
    *found_node = p; 
  } else if (cond < 0) {  /* less than into left subtree */
    p->left = addtree(p->left, w, found_node);
  } else {  /* greater than into right subtree */
    p->right = addtree(p->right, w, found_node);
  }

  return p;
}

/* treeprint: in-order print of tree p */
void treeprint(tnode *p, void (*print_extra)(void*))
{
  if (p != NULL) {
    treeprint(p->left, print_extra);
    printf("%4d %s\n", p->count, p->word);
    if(print_extra != NULL) {
      print_extra(p->extra_data);
    }
    treeprint(p->right, print_extra);
  }
}

