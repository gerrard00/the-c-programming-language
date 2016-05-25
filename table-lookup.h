/* copied from The C programming Langage 2nd Edition */
#ifndef TABLE_LOOKUP_H
#define TABLE_LOOKUP_H

struct nlist{ 			/*table entry:*/
	struct nlist *next; /*next entry in chain*/
	char *name; 				/*defined name*/
	char *defn; 				/*replacementtext*/
};

struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
void undef(char *name);
void printtable();

#endif /* TABLE_LOOKUP_H */
