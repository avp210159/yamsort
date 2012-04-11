// avp sorts 2011 C "template" implementation merge sort, symmerge sort
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#ifndef SORT_NAME
#error "Must declare SORT_NAME"
#endif

#ifndef SORT_TYPE
#error "Must declare SORT_TYPE"
#endif

#ifndef SORT_CMP
#define SORT_CMP(x, y)  ((x) < (y) ? -1 : ((x) == (y) ? 0 : 1))
#endif



#define SORT_SWAP(x,y) ({SORT_TYPE __SORT_SWAP_t = (x); (x) = (y); (y) = __SORT_SWAP_t;})

#define SORT_CONCAT(x, y) x ## _ ## y
#define SORT_MAKE_STR1(x, y) SORT_CONCAT(x,y)
#define SORT_MAKE_STR(x) SORT_MAKE_STR1(SORT_NAME,x)


#define MMERGE_SORT            SORT_MAKE_STR(mmsort)
#define SYMM_SORT              SORT_MAKE_STR(symsort)

void MMERGE_SORT  (SORT_TYPE *dst, const size_t size);
void SYMM_SORT    (SORT_TYPE *dst, const size_t size);



// trivial merge sort (1/2 aux memory N (log N) complexity )
static void
mmerge (SORT_TYPE a[], SORT_TYPE tmp[], 
	size_t l, size_t r, size_t rlast)
{
  if (SORT_CMP(a[r-1],a[r]) <= 0)
    return;
  size_t i, k = r-l, j;

  memcpy (tmp,a+l,k*sizeof(*a));
  for (i = 0, j = r; i < k && j <= rlast;) {
    if (SORT_CMP(tmp[i],a[j]) <= 0)
      a[l++] = tmp[i++];
    else
      a[l++] = a[j++];
  }
  while (i < k)
    a[l++] = tmp[i++];
}


static void
mmsort (SORT_TYPE a[], SORT_TYPE tmp[], size_t first, size_t last)
{
  if (first < last) {
    size_t mid = (first+last) >> 1, i, j;
    if (last-first < 65) {
      //      BINARY_INSERTION_SORT(a+first, last-first+1);
      SORT_TYPE t;

      for (i = first+1; i <= last; i++) {
	t = a[i];
	for (j = i; j > first; j--) {
	  if (SORT_CMP(t,a[j-1]) < 0)
	    a[j] = a[j-1];
	  else
	    break;
	}
	a[j] = t;
      }
    } else {
      mmsort (a,tmp,first,mid);
      mmsort (a,tmp,mid+1,last);
      mmerge (a,tmp,first,mid+1,last);
    }
  }
}


void 
MMERGE_SORT (SORT_TYPE *dst, const size_t size)
{
  SORT_TYPE *tmp = (SORT_TYPE *)malloc ((size/2+1)*sizeof(*dst));

  mmsort (dst,tmp,0,size-1);
  free(tmp);
}



/*
 symmerge sort (No aux memory, N (log N)^2 complexity (?) )

  based on
  http://ak.hanyang.ac.kr/papers/esa2004.pdf

  Stable Minimum Storage Merging by Symmetric
  Comparisons
  Pok-Son Kim and Arne Kutzner
*/

static void inline
pswap (SORT_TYPE *a, size_t f, size_t t, size_t l)
{
  for (l+=f; f < l; f++,t++)
    SORT_SWAP(a[f],a[t]);
}

static void
rotate (SORT_TYPE *a, size_t l, size_t r, size_t end)
{
  size_t n = end-l, dist = r-l;
  if (dist == 0 || dist == n)
    return;
  a += l;
  size_t i,j,p;
  i = p = dist;
  j = n - p;
  while (i != j) {
    if (i > j) {
      pswap (a, p-i,p,j);
      i -= j;
    } else {
      pswap (a, p-i,p+j-i,i);
      j -= i;
    }
  }
  pswap (a, p-i,p,i);

}


static size_t
Bsearch (SORT_TYPE *a, size_t l, size_t r, size_t p)
{
  size_t m;
  while (l < r) {
    m = (l+r) >> 1;
    if (SORT_CMP(a[m],a[p-m]) <= 0)
      l = m+1;
    else
      r = m;
  }
  return l;
}


static void
symmerge (SORT_TYPE *a, size_t first1, size_t first2, size_t last)
{
  size_t start, end, m, n;

  if (last - first1 < 9) {
    // insertion merge (947 ms work lim == 9)
    size_t f2, p, q;

    for (f2 = first2; f2 < last; f2++) {
      for (p = f2, q = f2-1; p > first1; p--,q--) {
	if (SORT_CMP(a[p],a[q]) >= 0)
	  break;
	SORT_SWAP(a[p],a[q]);
      }
    }
    return;
  }
  if (first1 < first2 && first2 < last) {
    m = (first1 + last)/2;
    n =  m + first2;
    if (first2 > m) {
      start =  Bsearch (a, n - last, m, n - 1);
    } else { 
      start =  Bsearch (a, first1, first2, n - 1);
    }
    end = n - start;

    rotate (a, start, first2, end);
    symmerge (a, first1, start, m);
    symmerge (a, m, end, last);
  }

}

static void
symmsort (SORT_TYPE *a, size_t f, size_t n)
{
  if (n-f > 1) {
    size_t m = (f+n) >> 1;

    symmsort (a,f,m);
    symmsort (a,m,n);
    symmerge (a,f,m,n);
  }
}

void
SYMM_SORT (SORT_TYPE *dst, const size_t size)
{
  symmsort (dst,0,size);
}



#undef SORT_CONCAT
#undef SORT_MAKE_STR1
#undef SORT_MAKE_STR
#undef SORT_NAME
