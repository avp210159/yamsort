#include <stdlib.h>

/*
  Programm written by avp 2012

  based on
  http://ak.hanyang.ac.kr/papers/esa2004.pdf

  Stable Minimum Storage Merging by Symmetric
  Comparisons
  Pok-Son Kim and Arne Kutzner

  Сортировка слиянием "на месте" (Symmerge)
  время д.б. O(N (log N)^2)
  не выделяем "вспомогательную" память
*/


/*
  поменять l элементов, начинающихся в a[f] с элементами из a[t]
  sz размер элемента в байтах
 */
static inline void 
swap (void *a, int sz, int f, int t, int l)
{
  char tt;
  char *af = (char *)a+f*sz, *at = (char *)a+t*sz, *al;

  al = af+l*sz;
  while (af < al) {
    tt = *af;
    *af++ = *at;
    *at++ = tt;
  }
}

/*
  вращать отрезок массива a[left]...a[r]...a[end-1]
  (размер элемента size байт) 
  так, чтобы a[left] занял место a[r]
  Алгоритм из   http://codelab.ru/task/cycle_shift/
 */
static void
rotate (void *a,int size, int left, int r, int end)
{
  int  n = end-left, dist = r-left;
  if (dist == 0 || dist == n)
    return;
  a += left*size;
  int i, j, p;
  i = p = dist;
  j = n - p;
  while (i != j) {
    if (i > j) {
      swap (a,size, p-i,p,j);
      i -= j;
    } else {
      swap (a,size, p-i,p+j-i,i);
      j -= i;
    }
  }
  swap (a,size, p-i,p,i);
}


/*
  Bsearch из http://ak.hanyang.ac.kr/papers/esa2004.pdf
 */
static int
smbsearch (void *a, int l, int r, int p, int size,
      int (*cmp)(const void *, const void *))
{
  int m;
  while (l < r) {
    m = (l +r)/2;
    if (cmp(a+m*size,a+(p-m)*size) <= 0)
      l = m+1;
    else
      r = m;
  }
  return l;
}

/*
  в основном Symmerge из http://ak.hanyang.ac.kr/papers/esa2004.pdf
  для маленьких сливаемых подмассивов применяем слияние вставками
  вместо рекурсии
 */
static void
symmerge (void *a, 
	  int first1,   // index of first in array1
	  int first2,   // index of first in array2
	  int last,     // index of first after array2
	  int size, 
	  int (*cmp)(const void *, const void *))
{
  int start, end, m, n;

  if (last - first1 < 9) {
    // insertion merge 
    char *f1 = a+first1*size, *f2 = a+first2*size, *p, *q, *t, *e = a+last*size;
    for  (; f2 < e; f2 += size) {
      for (p = f2; p > f1; p -=size) {
	if (cmp(t=p,q=p-size) >= 0)
	  break;
	while (q < p) {
	  char tt = *q;
	  *q++ = *t;
	  *t++ = tt;
	}
      }
    }
    return;
  }

  // Symmerge
  if (first1 < first2 && first2 < last) {
    m = (first1 + last)/2;
    n =  m + first2;
    if (first2 > m) {
      start =  smbsearch (a, n - last, m, n - 1, size,cmp);
    } else { 
      start =  smbsearch (a, first1, first2, n - 1, size,cmp);
    }
    end = n - start;

    rotate (a,size, start, first2, end);
    symmerge (a, first1, start, m, size,cmp);
    symmerge (a, m, end, last, size,cmp);
  }
}

/*
  Обычная сортировка слиянием (рекурсивное деление массива пополам)
  с переходом к сортировке слиянием для маленьких подмассивов
 */
static void 
sort (void *a, int f, int n, int size, 
      int (*cmp)(const void *, const void *))
{
  if (n - f < 31) {
    // insertion sort
    void *p, *q, *first = a + size*f, *last = a + size*n;
    char *cf, *ct, *ce, tt;

    for (p = first+size; p < last; p+=size) {
      for (q = p; q > first; q-=size) {
	if (cmp(q-size,q) <= 0)
	  break;
	//	swap(q-size,q,size); 
	cf = q-size; ct = q;
	while (cf < (char *)q) {
	  tt = *cf;
	  *cf++ = *ct;
	  *ct++ = tt;
	}
      }
    }
  } else {
    int m = (f+n) >> 1;
    sort (a,f,m,size,cmp);
    sort (a,m,n,size,cmp);
    symmerge (a,f,m,n,size,cmp);
  }
}

// qsort style interface
void
symmsort (void *a, 
	size_t total_elems,  
	size_t elem_size, 
	int (*cmp)(const void *, const void *))
{
  sort (a,0,total_elems,elem_size,cmp);
}

