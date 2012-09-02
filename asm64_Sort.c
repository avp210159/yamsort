#include <stdio.h>
#include <stdlib.h>

#ifdef ASM64
#include "Sort.h"
#endif

void
asm64_intqs (int *a, size_t n)
{
#ifdef ASM64
  Array_QuickSortAsc_sint32(a,n);
#else
  printf ("Array_QuickSortAsc_sint32() Not implemented\n");
#endif
}

static int *tmp = NULL, ntmp;

void
asm64_freetmp ()
{
  if (tmp) {
    free(tmp);
    tmp = NULL;
  }
}

void
asm64_intrs (int *a, size_t n)
{
#ifdef ASM64
  if (!tmp) {
    if (!(tmp = malloc(n*sizeof(*a)))) {
      printf ("No memory for tmp array\n");
      return;
    }
    ntmp = n;
  }

  if (n > ntmp) {
    int *old = tmp;
    if (!(tmp = realloc(tmp,n*sizeof(*a)))) {
      printf ("No memory for tmp array\n");
      free(old);
      return;
    }
    ntmp = n;
  }

  Array_RadixSortAsc_sint32(a,tmp,n);

#else
  printf ("Array_RadixSortAsc_sint32() Not implemented\n");
#endif
}
