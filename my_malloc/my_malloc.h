#ifndef MY_ALLOC_H
#define MY_ALLOC_H

void *my_malloc(unsigned nbytes);
void *my_calloc(unsigned nbytes);
void my_free(void *ap);
void my_dump(void);
void bfree(void *p, unsigned n);

#endif
