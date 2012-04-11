/*
  timsort with interface identical qsort


   Author
   ------
   Vasily Anishchenko (avp210159@mail.ru)

  

   This code based on "template" C implementation of timsort by
   Christopher Swenson (chris@caswenson.com)

  License from original README.rst

All code in this repository, unless otherwise specified, is hereby
licensed under the MIT Public License:

Copyright (c) 2010 Christopher Swenson

 Permission is hereby granted, free of charge, to any person
 obtaining a copy of this software and associated documentation
 files (the "Software"), to deal in the Software without
 restriction, including without limitation the rights to use,
 copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the
 Software is furnished to do so, subject to the following
 conditions:

 The above copyright notice and this permission notice shall be
 included in all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 OTHER DEALINGS IN THE SOFTWARE.

 */



#define SORT_TYPE char

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

#if 0
#ifndef SORT_CMP
#define SORT_CMP(x, y)  ((x) < (y) ? -1 : ((x) == (y) ? 0 : 1))
#endif
#endif

#define SORT_SWAP(x,y) ({SORT_TYPE __SORT_SWAP_t = (x); (x) = (y); (y) = __SORT_SWAP_t;})


/* Byte-wise swap two items of size SIZE. */
#define SWAP(a, b, size)						      \
  do									      \
    {									      \
      register size_t __size = (size);					      \
      register char *__a = (a), *__b = (b);				      \
      do								      \
	{								      \
	  char __tmp = *__a;						      \
	  *__a++ = *__b;						      \
	  *__b++ = __tmp;						      \
	} while (--__size > 0);						      \
    } while (0)

#ifndef MAX
#define MAX(x,y) (((x) > (y) ? (x) : (y)))
#endif
#ifndef MIN
#define MIN(x,y) (((x) < (y) ? (x) : (y)))
#endif


#ifndef CLZ
#ifdef __GNUC__
#define CLZ __builtin_clzll
#else

// adapted from Hacker's Delight
int clzll(uint64_t x) {
  int n;

  if (x == 0) return(64);
  n = 0;
  if (x <= 0x00000000FFFFFFFFL) {n = n + 32; x = x << 32;}
  if (x <= 0x0000FFFFFFFFFFFFL) {n = n + 16; x = x << 16;}
  if (x <= 0x00FFFFFFFFFFFFFFL) {n = n + 8; x = x << 8;}
  if (x <= 0x0FFFFFFFFFFFFFFFL) {n = n + 4; x = x << 4;}
  if (x <= 0x3FFFFFFFFFFFFFFFL) {n = n + 2; x = x << 2;}
  if (x <= 0x7FFFFFFFFFFFFFFFL) {n = n + 1;}
  return n;
}

#define CLZ clzll
#endif
#endif


/* Function used to do a binary search for binary insertion sort */
static inline int64_t 
binary_insertion_find(SORT_TYPE *dst, 
		      const SORT_TYPE x[], 
		      const size_t size,
		      int _sz_,
		      int (*SORT_CMP)(const void *, const void *))
{
  int64_t l, c, r;
  l = 0;
  r = size - 1;
  c = r >> 1;
  SORT_TYPE lx[_sz_], cx[_sz_], rx[_sz_];
  //  lx = dst[l];
  memcpy (lx,dst+l*_sz_,_sz_);
  
  /* check for beginning conditions */
  if (SORT_CMP(x, lx) < 0)
    return 0;
  else if (SORT_CMP(x, lx) == 0)
  {
    int64_t i = 1;
    while (SORT_CMP(x, dst+i*_sz_) == 0) i++;
    return i;
  }
  
  //  rx = dst[r];
  memcpy(rx,dst+r*_sz_,_sz_);
  // guaranteed not to be >= rx
  //  cx = dst[c];
  memcpy(cx,dst+c*_sz_,_sz_);
  while (1)
  {
    const int val = SORT_CMP(x, cx);
    if (val < 0)
    {
      if (c - l <= 1) return c;
      r = c;
      //      rx = cx;
      memcpy(rx,cx,_sz_);
    }
    else if (val > 0)
    {
      if (r - c <= 1) return c + 1;
      l = c;
      //      lx = cx;
      memcpy(lx,cx,_sz_);
    }
    else
    {
      do
      {
	//        cx = dst[++c];
	++c;
	memcpy(cx,dst+c*_sz_,_sz_);
      } while (SORT_CMP(x, cx) == 0);
      return c;
    }
    c = l + ((r - l) >> 1);
    //    cx = dst[c];
    memcpy(cx,dst+c*_sz_,_sz_);
  }
}


/* Binary insertion sort, but knowing that the first "start" entries are sorted.  Used in timsort. */
static inline void 
binary_insertion_sort_start(SORT_TYPE *dst, 
			    const size_t start, 
			    const size_t size,
			    int _sz_,
			    int (*SORT_CMP)(const void *, const void *))
{
  int64_t i;
  char *pdi, *pdj;
  for (i = start, pdi = dst+start*_sz_; i < size; i++, pdi+=_sz_)
  {
    int64_t j;
    /* If this entry is already correct, just move along */
    //    if (SORT_CMP(&dst[i - 1], &dst[i]) <= 0) continue;
    //    if (SORT_CMP(dst+(i-1)*_sz_,dst+i*_sz_) <= 0)  continue;
    if (SORT_CMP(pdi-_sz_,pdi) <= 0)  continue;
    
    /* Else we need to find the right place, shift everything over, and squeeze in */
    SORT_TYPE x[_sz_];// = dst[i];
    //    memcpy(x,dst+i*_sz_,_sz_);
    memcpy(x,pdi,_sz_);
    int64_t location = binary_insertion_find(dst, x, i, _sz_,SORT_CMP);
    char *ploc = dst+location*_sz_;
    //    for (j = i - 1, pdj = pdi-_sz_; j >= location; j--, pdj-=_sz_)
    for (pdj = pdi-_sz_; pdj >= ploc; pdj-=_sz_)
    {
      //dst[j + 1] = dst[j];
      //      memcpy(dst+(j+1)*_sz_, dst+j*_sz_, _sz_);
      memcpy (pdj+_sz_, pdj, _sz_);
    }
    //    dst[location] = x;
    //    memcpy(dst+location*_sz_,x,_sz_);
    memcpy(ploc,x,_sz_);
  }
}

/* Binary insertion sort */
static void 
BINARY_INSERTION_SORT(SORT_TYPE *dst, 
		      const size_t size,
		      int _sz_,
		      int (*SORT_CMP)(const void *, const void *))
{
  binary_insertion_sort_start(dst, 1, size, _sz_,SORT_CMP);
}



typedef struct {
  size_t alloc;
  SORT_TYPE *storage;
} TEMP_STORAGE_T;


typedef struct {
  int64_t start;
  int64_t length;  
} TIM_SORT_RUN_T;


/* timsort implementation, based on timsort.txt */

static inline void 
reverse_elements(SORT_TYPE *dst, int64_t start, int64_t end, int _sz_)
{
  while (1)
  {
    if (start >= end) return;
    //SORT_SWAP(dst[start], dst[end]);
    SWAP(dst+start*_sz_, dst+end*_sz_, _sz_);
    start++;
    end--;
  }
}

static inline int64_t 
count_run(SORT_TYPE *dst, const int64_t start, const size_t size, int _sz_,
	  int (*SORT_CMP)(const void *, const void *))
{
  if (size - start == 1) return 1;
  if (start >= size - 2)
  {
    if (SORT_CMP(&dst[(size - 2)*_sz_], &dst[(size - 1)*_sz_]) > 0)
      //      SORT_SWAP(dst[size - 2], dst[size - 1]);
      SWAP(dst+(size-2)*_sz_, dst+(size-1)*_sz_, _sz_);

    return 2;
  }
  
  int64_t curr = start + 2;
  
  if (SORT_CMP(&dst[start*_sz_], &dst[(start + 1)*_sz_]) <= 0)
  {
    // increasing run
    while (1)
    {
      if (curr == size - 1) break;
      if (SORT_CMP(&dst[(curr - 1)*_sz_], &dst[curr*_sz_]) > 0) break;
      curr++;
    }
    return curr - start;    
  }
  else
  {
    // decreasing run
    while (1)
    {
      if (curr == size - 1) break;
      if (SORT_CMP(&dst[(curr - 1)*_sz_], &dst[curr*_sz_]) <= 0) break;
      curr++;
    }
    // reverse in-place
    reverse_elements(dst, start, curr - 1, _sz_);
    return curr - start;
  }
}

static inline int compute_minrun(const uint64_t size)
{
  const int top_bit = 64 - CLZ(size);
  const int shift = MAX(top_bit, 6) - 6;
  const int minrun = size >> shift;
  const uint64_t mask = (1ULL << shift) - 1;
  if (mask & size) return minrun + 1;
  return minrun;
}

  
static inline int check_invariant(TIM_SORT_RUN_T *stack, const int stack_curr)
{
  if (stack_curr < 2) return 1;
  if (stack_curr == 2)
  {
    const int64_t A = stack[stack_curr - 2].length;
    const int64_t B = stack[stack_curr - 1].length;
    if (A <= B) return 0;
    return 1;
  }
  const int64_t A = stack[stack_curr - 3].length;
  const int64_t B = stack[stack_curr - 2].length;
  const int64_t C = stack[stack_curr - 1].length;
  if ((A <= B + C) || (B <= C)) return 0;
  return 1;
}

int nrealloc = 0;

static inline void 
tim_sort_resize(TEMP_STORAGE_T *store, const size_t new_size, int _sz_)
{
  if (store->alloc < new_size)
  {
    SORT_TYPE *tempstore = realloc(store->storage, 
				   new_size * _sz_);

    nrealloc++;
    if (tempstore == NULL)
    {
      fprintf(stderr, "Error allocating temporary storage for tim sort: need %lu bytes", (long)(sizeof(SORT_TYPE) * new_size * _sz_));
      exit(1);
    }
    store->storage = tempstore;
    store->alloc = new_size;
  }
}

static inline void 
tim_sort_merge(SORT_TYPE *dst, 
	       const TIM_SORT_RUN_T *stack, 
	       const int stack_curr, 
	       TEMP_STORAGE_T *store,
	       int _sz_,
	       int (*SORT_CMP)(const void *, const void *))
{
  const int64_t A = stack[stack_curr - 2].length;
  const int64_t B = stack[stack_curr - 1].length;
  const int64_t curr = stack[stack_curr - 2].start;

  tim_sort_resize(store, MIN(A, B), _sz_);
  SORT_TYPE *storage = store->storage;
  
  int64_t i, j, k;

  // left merge
  if (A < B)
  {
    memcpy(storage, &dst[curr*_sz_], A * sizeof(SORT_TYPE)*_sz_);
    i = 0;
    j = curr + A;
    
    for (k = curr; k < curr + A + B; k++)
    {
      if ((i < A) && (j < curr + A + B))
      {
        if (SORT_CMP(&storage[i*_sz_], &dst[j*_sz_]) <= 0) {
	  //          dst[k] = storage[i++];
	  memcpy(dst+k*_sz_, storage+i*_sz_,_sz_);
	  i++;
	} else {
	  //          dst[k] = dst[j++];          
	  memcpy(dst+k*_sz_, dst+j*_sz_,_sz_);
	  j++;
	}
      }
      else if (i < A)
      {
	//        dst[k] = storage[i++];
	memcpy(dst+k*_sz_, storage+i*_sz_,_sz_);
	i++;
      }
      else {
	//        dst[k] = dst[j++];
	memcpy(dst+k*_sz_, dst+j*_sz_,_sz_);
	j++;
      }
    }
  }
  // right merge
  else
  {    
    memcpy(storage, &dst[(curr + A)*_sz_], B * sizeof(SORT_TYPE)*_sz_);
    i = B - 1;
    j = curr + A - 1;
    
    for (k = curr + A + B - 1; k >= curr; k--)
    {
      if ((i >= 0) && (j >= curr))
      {
	if (SORT_CMP(&dst[j*_sz_], &storage[i*_sz_]) > 0) {
	  //            dst[k] = dst[j--];
	  memcpy(dst+k*_sz_, dst+j*_sz_,_sz_);
	  j--;
	} else {
	  //            dst[k] = storage[i--];          
	  memcpy(dst+k*_sz_, storage+i*_sz_,_sz_);
	  i--;
	}
      }
      else if (i >= 0) {
	//        dst[k] = storage[i--];
	memcpy(dst+k*_sz_, storage+i*_sz_,_sz_);
	i--;
      } else {
	//        dst[k] = dst[j--];
	memcpy(dst+k*_sz_, dst+j*_sz_,_sz_);
	j--;
      }
    }
  }
}

static inline int 
tim_sort_collapse(SORT_TYPE *dst, 
		  TIM_SORT_RUN_T *stack, 
		  int stack_curr, 
		  TEMP_STORAGE_T *store, 
		  const size_t size,
		  int _sz_,
		  int (*SORT_CMP)(const void *, const void *))
{
  while (1)
  {
    // if the stack only has one thing on it, we are done with the collapse
    if (stack_curr <= 1) break;
    // if this is the last merge, just do it
    if ((stack_curr == 2) && (stack[0].length + stack[1].length == size))
    {
      tim_sort_merge(dst, stack, stack_curr, store, _sz_,SORT_CMP);
      stack[0].length += stack[1].length;
      stack_curr--;
      break;
    }
    // check if the invariant is off for a stack of 2 elements
    else if ((stack_curr == 2) && (stack[0].length <= stack[1].length))
    {
      tim_sort_merge(dst, stack, stack_curr, store, _sz_,SORT_CMP);
      stack[0].length += stack[1].length;
      stack_curr--;
      break;
    }
    else if (stack_curr == 2)
      break;
      
    const int64_t A = stack[stack_curr - 3].length;
    const int64_t B = stack[stack_curr - 2].length;
    const int64_t C = stack[stack_curr - 1].length;
    
    // check first invariant
    if (A <= B + C)
    {
      if (A < C)
      {
        tim_sort_merge(dst, stack, stack_curr - 1, store, _sz_,SORT_CMP);
        stack[stack_curr - 3].length += stack[stack_curr - 2].length;
        stack[stack_curr - 2] = stack[stack_curr - 1];
        stack_curr--;
      }
      else
      {
        tim_sort_merge(dst, stack, stack_curr, store, _sz_,SORT_CMP);
        stack[stack_curr - 2].length += stack[stack_curr - 1].length;
        stack_curr--;
      }
    }
    // check second invariant
    else if (B <= C)
    {
      tim_sort_merge(dst, stack, stack_curr, store, _sz_,SORT_CMP);
      stack[stack_curr - 2].length += stack[stack_curr - 1].length;
      stack_curr--;      
    }
    else
      break;
  }
  return stack_curr;
}


#define PUSH_NEXT() do {\
    len = count_run(dst, curr, size, _sz_,SORT_CMP);	\
run = minrun;\
if (run < minrun) run = minrun;\
if (run > size - curr) run = size - curr;\
if (run > len)\
{\
  binary_insertion_sort_start(&dst[curr*_sz_], len, run, _sz_,SORT_CMP); \
  len = run;\
}\
run_stack[stack_curr++] = (TIM_SORT_RUN_T) {curr, len};\
curr += len;\
if (curr == size)\
{\
  /* finish up */ \
  while (stack_curr > 1) \
  { \
    tim_sort_merge(dst, run_stack, stack_curr, store, _sz_,SORT_CMP);	\
    run_stack[stack_curr - 2].length += run_stack[stack_curr - 1].length; \
    stack_curr--; \
  } \
  if (store->storage != NULL)\
  {\
    free(store->storage);\
    store->storage = NULL;\
  }\
  return;\
}\
}\
while (0)


//void TIM_SORT(SORT_TYPE *dst, const size_t size)
static void 
otimsorti(SORT_TYPE *dst, const size_t size, int _sz_,
	       int (*SORT_CMP)(const void *, const void *))
{
  if (size < 64)
  {
    BINARY_INSERTION_SORT(dst, size, _sz_,SORT_CMP);
    return;
  }
  
  // compute the minimum run length
  const int minrun = compute_minrun(size);
  
  // temporary storage for merges
  TEMP_STORAGE_T _store, *store = &_store;
  store->alloc = 0;
  store->storage = NULL;
  
  TIM_SORT_RUN_T run_stack[128];
  int stack_curr = 0;
  int64_t len, run;
  int64_t curr = 0;
  
  PUSH_NEXT();
  PUSH_NEXT();
  PUSH_NEXT();
  
  while (1)
  {
    if (!check_invariant(run_stack, stack_curr))
    {
      stack_curr = tim_sort_collapse(dst, run_stack, 
				     stack_curr, store, size, _sz_,SORT_CMP);
      continue;
    }
    PUSH_NEXT();
  }
}


void 
timsort (void *arr, int n, int sz, 
		       int (*fpcmp)(const void *, const void *))
{
  //  SORT_CMP = fpcmp;
  //  _sz_ = sz;
  otimsorti (arr, n, sz, fpcmp);
}
