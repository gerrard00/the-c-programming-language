#include <stdio.h>
#include <limits.h>
#include "my_malloc.h"

typedef long Align; /* for alignment to long boundary */

union header {
  struct {
    union header *ptr;  /* block header */
    unsigned size;      /* size of this block */
  } s;
  Align x;
};

typedef union header Header;

static Header base; /* empty list to get started */
static Header *freep = NULL; /* start of free list */

static Header *morecore(unsigned);

/* set plausible limit for my_malloc. Keep in mind
 * modern C uses size_t, because unsigned is too small.
 * Artificially set this to unsigned max - 10 for
 * the exercise, even though that's unrealistic */
#define MAX_ALLOWED_MALLOC UINT_MAX - 10

/* malloc: general-purpose storage allocator */
void *my_malloc(unsigned nbytes)
{
  Header *p, *prevp;
  unsigned nunits;

  /* request is too big */
  if (nbytes > MAX_ALLOWED_MALLOC) {
    return NULL;
  }

  nunits = (nbytes + sizeof(Header) - 1)/sizeof(Header) + 1;
  if ((prevp = freep) == NULL) {
    base.s.ptr = freep = prevp = &base;
    base.s.size = 0;
  }

  for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
    if (p->s.size >= nunits) { /* big enough */
      if (p->s.size == nunits) { /* exactly */
        prevp->s.ptr = p->s.ptr;
      } else {  /* allocate tail end */
        p->s.size -= nunits;
        p += p->s.size;
        p->s.size = nunits;
      }
      freep = prevp;
      return (void *) (p+1);
    }
    if (p == freep) { /* wrapped around free list */
      if ((p = morecore(nunits)) == NULL) {
        return NULL; /* none left */
      }
    }
  }
}

#define NALLOC 1024 /* minimum #units to request */

/* morecore: ask system for more memory */
static Header *morecore(unsigned nu)
{
  char *cp, *sbrk(int);
  Header *up;

  if (nu < NALLOC) {
    nu = NALLOC;
  }
  cp = sbrk(nu * sizeof(Header));
  if(cp == (char *) -1)  { /* no space at all */
    return NULL;
  }
  up = (Header *)cp;
  up->s.size = nu;
  my_free((void *)(up+1));
  return freep;
}

/* free: put block ap in free list */
void my_free(void *ap)
{
  Header  *bp, *p;

  if (ap == NULL) {
    // debug
    printf("Null pointer\n");
    return;
  }

  bp = (Header *)ap - 1; /* point to block header */

  // check to make sure size is plausible
  if (bp->s.size == 0 || bp->s.size > MAX_ALLOWED_MALLOC) {
    // debug
    printf("Invalid size %u\n", bp->s.size);
    return;
  }

  for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr) {
    if (p >= p->s.ptr && (bp > p || bp < p->s.ptr)) {
      break; /* freed block at start or end of area */
    }
  }

  if (bp + bp->s.size == p->s.ptr) { /* join to upper nbr */
    bp->s.size += p->s.ptr->s.size;
    bp->s.ptr = p->s.ptr->s.ptr;
  } else {
    bp->s.ptr = p->s.ptr;
  }
  if (p + p->s.size == bp) { /* join to lower nbr */
    p->s.size += bp->s.size;
    p->s.ptr = bp->s.ptr;
  } else {
    p->s.ptr = bp;
  }
  freep = p;
}

void *my_calloc(unsigned nbytes)
{
  char *result = my_malloc(nbytes);

  if (result != NULL) {
    for(unsigned i = 0; i < nbytes; i++) {
      *(result + i) = 0;
    }
  }

  return result;
}
