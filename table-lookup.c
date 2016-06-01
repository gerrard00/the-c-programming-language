#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table-lookup.h"

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE]; /*pointer table*/

/* hash:form hash value for string s*/
unsigned hash(char*s)
{
  unsigned hashval;

  for (hashval = 0; *s != '\0'; s++) {
    hashval = *s + 31 * hashval;
  }
  return hashval % HASHSIZE;
}


/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
  struct nlist *np;

  for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
    if (strcmp(s, np->name) == 0) {
      return np; /* found */
    }
  }

  return NULL; /*not found*/
}

/* install:put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
  struct nlist *np;
  unsigned hashval;

  if ((np = lookup(name)) == NULL) { /* not found */
    np = (struct nlist *) malloc(sizeof(*np));
    if (np == NULL || (np->name = strdup(name)) == NULL) {
      return NULL;
    }
    hashval = hash(name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  } else { /* already there */
    free((void*) np->defn); /* free previous defn */
  }
  if ((np->defn = strdup(defn)) == NULL) {
    return NULL;
  }

  return np;
}

void undef(char *name)
{
  struct nlist *np;
  struct nlist *np_previous = NULL;
  int hashed_name = hash(name);

  for (np = hashtab[hashed_name]; np != NULL; np = np->next) {
    if (strcmp(name, np->name) == 0) {
      if (np_previous != NULL) {
        np_previous->next = np->next;
        return;
      } else {
        //it's the first link in the chain
        hashtab[hashed_name] = NULL;
      }
    }
    np_previous = np;
  }
}

void printtable()
{
  for(int i = 0; i < HASHSIZE; i++) {
    for(struct nlist *current = hashtab[i];
        current != NULL; current = current->next) {

      printf("%s\t\t%s\n", current->name, current->defn);
    }
  }

  printf("\n");
}
