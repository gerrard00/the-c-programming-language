/* copied from The C programming Langage 2nd Edition */
#include "binary-tree-with-key.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/* talloc: make a tnode */
tnode *talloc(void) 
{
  return (tnode *) malloc(sizeof(tnode));
}

/* addtree: add a node with w, at or below p */
tnode *addtree(tnode *p, char *key, char *w) 
{
  int cond;

  if(p == NULL) {   /* a new word has arrived */
    p = talloc();   /* make a new node */
    p->key = strdup(key);
    p->word = strdup(w);
    p->count = 1;
    p->left = p->right = NULL;
  } else if ((cond = strcmp(w, p->word)) == 0) {
    p->count++;   /* repeated word */
  } else if (cond < 0) {  /* less than into left subtree */
    p->left = addtree(p->left, key, w);
  } else {  /* greater than into right subtree */
    p->right = addtree(p->right, key, w);
  }

  return p;
}

/* treeprint: in-order print of tree p */
void treeprint(tnode *p)
{
  if (p != NULL) {
    treeprint(p->left);
    printf("%4d\t%s\t%s\n", p->count, p->key, p->word);
    treeprint(p->right);
  }
}

