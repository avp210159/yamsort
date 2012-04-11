#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
  ========== mmsort void   avp 2012 ========= 
  
  Тривиальная экономия памяти в сортировке слиянием.
  Поскольку при сортировке сами делим массив пополам,
  максимальная длина сливаемого подмассива это половина
  длины исходного массива,
  Выделяем вначале буфер такого размера и для всех
  слияний используем его, копируя туда первый из сливаемых
  подмассивов.
  Результат слияния получается "по месту".

*/

// merge for void
static void
merge (void *a, void *tmp, size_t size, 
	size_t l, size_t r, size_t rlast, 
	int (*fpcmp)(const void *, const void *))
{
  void *pr = a+r*size, *pl = a+l*size, *prl = a+(rlast+1)*size;
  if (fpcmp(pr-size,pr) <= 0)
    return;
  void *tend = tmp+(r-l)*size;
  memcpy (tmp,pl,tend-tmp); // first array
  while (tmp < tend && pr < prl) {
    if (fpcmp(tmp,pr) <= 0) {
      memcpy(pl,tmp,size);
      tmp += size;
    } else {
      memcpy(pl,pr,size);
      pr += size;
    }
    pl += size;
  }
  while (tmp < tend) {
    memcpy(pl,tmp,size);
    tmp += size;
    pl += size;
  }
}

static void inline
swap (char *f, char *t, int n)
{
  char tt, *end = f+n;

  while (f < end) {
    tt = *f;
    *f++ = *t;
    *t++ = tt;
  }

}

// insertion sort for void
static void inline
insort (void *a,     // base
	size_t size, // item size
	size_t l,    // first item in a[]
	size_t r,    // last item in a[]
	int (*fpcmp)(const void *, const void *))
{
  void *first = a + size*l, *last = a + size*r, *p, *q;

  for (p = first+size; p <= last; p+=size) {
    for (q = p; q > first; q-=size) {
      if (fpcmp(q-size,q) <= 0)
	break;
      swap (q-size,q,size);
    }
  }
}



// main msort for void
static void
sortm (void *a, void *tmp, size_t size,
       size_t first, size_t last, int (*fpcmp)(const void *, const void *))
{
  if (last-first < 33) {
    insort (a,size,first,last,fpcmp);
  } else {
    size_t mid = (first+last)/2;

    sortm (a,tmp,size,first,mid,fpcmp);
    sortm (a,tmp,size,mid+1,last,fpcmp);
    merge (a,tmp,size,first,mid+1,last,fpcmp);
  }
  
}


// caller for msort void in qsort style
void
mmsort (void *base,   // array
       size_t nmemb, // n_of_items
       size_t size,  // item size
       int (*fpcmp)(const void *, const void *))
{
  void *tmp = malloc((nmemb/2+1)*size);
  sortm (base,tmp,size,0,nmemb-1,fpcmp);
  free (tmp);
}


