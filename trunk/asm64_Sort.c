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

void
asm64_intrs (int *a, size_t n)
{
#ifdef ASM64
  int *tmp = malloc(n*sizeof(*a));
  if (!tmp) 
    printf ("No memory for tmp array\n");
  else
    Array_RadixSortAsc_sint32(a,tmp,n);
#else
  printf ("Array_RadixSortAsc_sint32() Not implemented\n");
#endif
}
