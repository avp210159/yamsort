/* yamsort. Yet another merge sort function with interface identical qsort


   Author
   ------
   Vasily Anishchenko (avp210159@mail.ru)

   Code is hereby licensed under the MIT Public License:

   Copyright (C) 2012 Vasily Anishchenko

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

   Данная лицензия разрешает, безвозмездно, лицам, получившим копию 
   данного программного обеспечения и сопутствующей документации 
   (в дальнейшем именуемыми "Программное Обеспечение"), использовать 
   Программное Обеспечение без ограничений, включая неограниченное право 
   на использование, копирование, изменение, объединение, публикацию, 
   распространение, сублицензирование и/или продажу копий Программного 
   Обеспечения, также как и лицам, которым предоставляется данное 
   Программное Обеспечение, при соблюдении следующих условий:

   Вышеупомянутый копирайт и данные условия должны быть включены 
   во все копии или значимые части данного Программного Обеспечения.

   ДАННОЕ ПРОГРАММНОЕ ОБЕСПЕЧЕНИЕ ПРЕДОСТАВЛЯЕТСЯ «КАК ЕСТЬ», 
   БЕЗ ЛЮБОГО ВИДА ГАРАНТИЙ, ЯВНО ВЫРАЖЕННЫХ ИЛИ ПОДРАЗУМЕВАЕМЫХ, 
   ВКЛЮЧАЯ, НО НЕ ОГРАНИЧИВАЯСЬ ГАРАНТИЯМИ ТОВАРНОЙ ПРИГОДНОСТИ, 
   СООТВЕТСТВИЯ ПО ЕГО КОНКРЕТНОМУ НАЗНАЧЕНИЮ И НЕНАРУШЕНИЯ ПРАВ. 
   НИ В КАКОМ СЛУЧАЕ АВТОРЫ ИЛИ ПРАВООБЛАДАТЕЛИ НЕ НЕСУТ ОТВЕТСТВЕННОСТИ 
   ПО ИСКАМ О ВОЗМЕЩЕНИИ УЩЕРБА, УБЫТКОВ ИЛИ ДРУГИХ ТРЕБОВАНИЙ ПО 
   ДЕЙСТВУЮЩИМ КОНТРАКТАМ, ДЕЛИКТАМ ИЛИ ИНОМУ, ВОЗНИКШИМ ИЗ, ИМЕЮЩИМ 
   ПРИЧИНОЙ ИЛИ СВЯЗАННЫМ С ПРОГРАММНЫМ ОБЕСПЕЧЕНИЕМ ИЛИ ИСПОЛЬЗОВАНИЕМ 
   ПРОГРАММНОГО ОБЕСПЕЧЕНИЯ ИЛИ ИНЫМИ ДЕЙСТВИЯМИ С ПРОГРАММНЫМ ОБЕСПЕЧЕНИЕМ. 

 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <sysexits.h>

#define YAMSORT_INSLIM 31

#include "yamsort.h"

/*
  I apologize for my bad English, so many comments in Russian.

  comments in English are made with the help of a translator google

  avp
 */

/*
  yamsort merge sort 1/12 N (?) aux memory, N (log N) complexity (?)

  Попытка  сделать еще  одну устойчивую  (stable)  сортировку слиянием
  (yet another merge sort) с минимальной вспомогательной памятью.

  Используем "стандартный" рекурсивный  алгоритм сортировки слиянием с
  делением  массива  пополам на  каждом  шаге.  Когда отрезок  массива
  становится короче YAMSORT_INSLIM сортируем его вставками. 

  Упорядоченные   массивы   перед   слиянием  расположены   в   памяти
  последовательно.    Идея   реализуемого   здесь  алгоритма   слияния
  заключается  в  размещении   элементов  одной  последовательности  в
  "очереди",   которая  по  возможности   размещается  на   месте  уже
  вставленных в результат элементов другой последовательности.
  
  Проводим  слияние  левой  и  правой  частей на  месте  левой  части.
  Элементы левой части последовательно перемещаются в очередь, которая
  состоит  из динамически  выделяемых блоков,  размером  sqrt(N). Если
  возможно, блок  размещается на освободившемся в  правой части месте,
  иначе  выделяется функцией  malloc().   Однажды выделенные  malloc()
  блоки  при освобождении из  очереди заносятся  в список  свободных и
  используются повторно. Освобождающиеся  блоки очереди, размещенные в
  массиве заносятся в свой список свободных.

  Блоки   очереди   на  месте   элементов   правой  части   выделяются
  последовательно.   Если   очередной  добавляемый  в  отсортированную
  последовательность  элемент  должен   попасть  в  первый  из  блоков
  очереди,  размещенных в правой  части, то  этот блок  перемещается в
  свободное место в правой части  массива или (свободного места нет) в
  один из malloc-блоков.


  Trying to  make one more  stable mergesort (Yet another  merge sort)
  with a minimum of auxiliary memory.

  Use the "standard" recursive  algorithm merge sort with dividing the
  array in  half at  each step.  When a segment  of the  array becomes
  shorter YAMSORT_INSLIM sort it using inserts.

  Ordered arrays  before the merge are in  memory consequentially. The
  idea of ​​this  merging algorithm is to deploy  elements of a sequence
  in  "Queue",  which is  possibly  located  on  the site  is  already
  inserted into the result of different sequence elements.
  
  We perform  merging left  and right  sides on the  left side  of the
  site.   Elements of  the left  side  has consistently  moved in  the
  queue, which consists of a dynamically allocated blocks size of sqrt
  (N). If possible, the unit is located on the right side of the freed
  place  otherwise allocated  function malloc  ().  Once  allocated by
  malloc () blocks during the liberation of the queue onto the list of
  free and  reused. Backordered queue  blocks placed in the  array are
  recorded in another free list.

  Queue  blocks on  the  right side  of  the site  elements stand  out
  consequentially.  If added to  the sorted sequence element must fall
  into the first queue block, placed on the right side, then the block
  is moved to free space on the  right side of the array or (no space)
  in the one of the malloc-block.

 */


// Блок очереди - заголовок и дальше массив данных 
// Queue block header
typedef struct {
  int fdata, ffree; // индексы первого занятого и свободного элемента data[]
  struct  qblock *next, *prev;
} QBLOCK_HDR;

// Queue block with data array
typedef struct qblock {
  QBLOCK_HDR h;
  char  data[1];
} Q_BLOCK;

// Блок управления очередью и свободными блоками
typedef struct {
  Q_BLOCK *head, *tail, 
    *flist,     // список свободных блоков, полученных malloc()
    *aflist;    // двусвязный список свободных блоков в правой части массива
  void  *ffree, // начало свободного места в правой части
    *falloc,    // первый блок очереди, размещенный в правой части
    *afirst,    // начало всего массива
    *alast;     // его конец
  int   bsize,  // количество элементов, размещаемых в блоке очереди
    esize,      // размер элемента массива в байтах
    totbsz;     // размер блока очереди в байтах
} DATA_QUEUE;
/*
// The control unit queue and free blocks
typedef struct {
  Q_BLOCK * head, * tail,
    * flist,   // ​​list of free blocks received malloc ()
    * aflist;  // doubly linked list of free blocks on the right side of the array
  void * ffree,// ​​the beginning of free space on the right side
    * falloc,  // ​​first block of the queue that is located on the right side
    * afirst,  // ​​the beginning of the array
    * alast;   // to the end
  int bsize,   // ​​number of items placed in the block queue
    totbsz;    // block size in bytes of the queue
} DATA_QUEUE;
*/


/*  
 *  head
 *
 *  Description:
 *      This function returns a pointer to the first element in the queue
 *
 *  Parameters:
 *      q: [in]
 *          Queue control block
 *
 *  Returns:
 *      Address of first queue element or NULL if queue is empty
 *
 *  Comments:
 *
 */
// возвращает указатель на первый элемент в очереди
static inline void *
head (DATA_QUEUE *q)
{
  if (q->head == NULL || q->head->h.fdata == q->head->h.ffree)
    return NULL;
  return q->head->data + q->head->h.fdata * q->esize;
}


/*  
 *  enq
 *
 *  Description:
 *      This function add an element to the tail of the queue
 *
 *  Parameters:
 *      q: [in/out]
 *          Queue control block
 *      lcur: [in]
 *          Address of the element moved to the queue
 *      rfile: [in]
 *          Address of current top of the right side of the array
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *
 */
// добавить элемент в хвост очереди
static void inline 
enq (DATA_QUEUE *q, void *lcur, void *rfile)
{
  if (q->tail->h.ffree >= q->bsize) { // нет места в хвосте блока
    // there is no room in the block
    Q_BLOCK *bp = q->aflist;
    if (bp) { // блок из списка свободных в массиве
      // is a block from the free list in the array
      if (q->aflist = bp->h.next)
	q->aflist->h.prev = NULL;
    } else {
      if ((char *)rfile - (char *)q->ffree > q->totbsz) {
	// разместим новый блок очереди в массиве
	// place a new block of the queue in the array
	bp = (Q_BLOCK *)q->ffree;
	q->ffree = (char *)q->ffree + q->totbsz;
	if (!q->falloc)  // размещаем первый блок в правой части
	  q->falloc = bp;// place the first block on the right side
      } else {
	// разместим новый блок очереди в malloc-блоке
	// place a new block of the queue in malloc-block
	if (bp = q->flist)      // пытаемся взять его из списка свободных
	  q->flist = bp->h.next;// trying to take it from the free list
	else {
	  bp = (Q_BLOCK *)malloc(q->totbsz);
	}
      }
    }
    // добавим новый блок в хвост очереди
    // add a new block to the tail of the queue
    bp->h.fdata = bp->h.ffree = 0;
    bp->h.prev = q->tail;
    bp->h.next = NULL;
    q->tail->h.next = bp;
    q->tail = bp;
  }
  // запишем элемент в конец блока
  // We write an element to the end of the block
  memcpy((char *)(q->tail->data)+q->tail->h.ffree*q->esize,
	 lcur,q->esize);
  q->tail->h.ffree++;
}

/*  
 *  movfalc
 *
 *  Description:
 *      This function copies a  block of queue, 
 *      placed in a memory of array to  the free space
 *
 *  Parameters:
 *      q: [in/out]
 *          Queue control block
 *      pj: [in]
 *          Address of current top of the right side of the array
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *      Скопируем блок очереди, размещенный в правой части массива,
 *      в который предстоит запись формируемого результата
 *      в свободную область массива или в malloc-блок.
 *      Здесь мы не берем свободные блоки очереди, размещенные в памяти
 *      массива, чтобы избежать "пробуксовки".
 *      Важно. movfalc() не вызывается до того, как ВСЕ элементы
 *      левой части будут перемещены в очередь.
 *
 *      Copy the block of queue, located on the right side of the array,
 *      which is formed to be a record result to the array free area 
 *      or in malloc-block.
 *      Here we do not accept free blocks queue, placed in memory
 *      of the array, to avoid "slippage".  
 *      It's important. movfalc () is not called until  all the elements
 *      the left side will be moved to the queue.
 *
 */
static inline void
movfalc (DATA_QUEUE *q, 
	 void *pj) // текущее начало правой части
{
  Q_BLOCK *bp, *p = (Q_BLOCK *)q->falloc;

  if (p->h.ffree == -1) {
    // свободный блок очереди в массиве (его копировать не надо)
    // free queue unit in the array (the copy is not necessary)
    q->falloc = (char *)q->falloc + q->totbsz;
    if (q->falloc >= q->ffree) { 
      // закончим игры с свободным местом в массиве
      // finish the game with a free space in the array
      q->falloc = q->aflist = NULL;
    } else {
      // удалим блок из списка свободных блоков в массиве
      // remove the unit from the list of free blocks in the array
      if (p->h.next)
	p->h.next->h.prev = p->h.prev;
      if (p->h.prev)
	p->h.prev->h.next = p->h.next;
      else  // it was the first in the list
	q->aflist = p->h.next; // он был первым в списке
    }
    return;
  }

  // найдем место для копии блока
  // find a place to copy the block
  if ((char *)pj - (char *)q->ffree > q->totbsz &&
      (char *)q->ffree + q->totbsz < (char *)q->alast) { 
    // в свободную зону в массиве
    // to a free area in the array
    bp = (Q_BLOCK *)q->ffree;
    q->ffree = (char *)q->ffree + q->totbsz;
  } else {
    // копировать в malloc блок
    // Copy to malloc-block
    if (!(bp = q->flist)) {
      bp = (Q_BLOCK *)malloc(q->totbsz);
    } else {
      q->flist = bp->h.next;
    }
  }

  memcpy(bp,p,q->totbsz);

  if (bp->h.next)
    bp->h.next->h.prev = bp;
  if (bp->h.prev)
    bp->h.prev->h.next = bp;
  if (q->head == p)
    q->head = bp;
  if (q->tail == p)
    q->tail = bp;

  /*
    скорректируем адрес первого блока очереди в правой части массива
    correct the address of the first block of queue on the right side 
    of the array
  */
  q->falloc = (char *)q->falloc + q->totbsz;
  if (q->falloc >= q->ffree)
    // Вот и все. Очереди  в правой части  больше нет и не будет
    // That's all. queue on the right side is no more and will not be
    q->falloc = NULL;
}

/*  
 *  deq
 *
 *  Description:
 *      This function removes an element from the head of the queue 
 *      and returns its address
 *
 *  Parameters:
 *      q: [in/out]
 *          Queue control block
 *
 *  Returns:
 *      Address of the former head of the queue element
 *
 *  Comments:
 *      An empty queue block is moved to the free list if the queue is not empty
 *
 */
// удаляет элемент из головы очереди и возвращает его значение
static inline void *
deq (DATA_QUEUE *q)
{
  void *pr = head(q);
  if (!pr) {
    fprintf (stderr,"yamsort merge internal error. empty queue\n");
    exit (EX_SOFTWARE);
  }
  int fd = q->head->h.fdata, ff = q->head->h.ffree;
  fd++;
  if (fd == ff) {
    // элементы очереди в этом блоке закончились 
    // queue elements in this unit ended
    if (q->tail == q->head) {
      q->head->h.fdata = q->head->h.ffree = 0; // make empty queue 
    } else {
      Q_BLOCK *bp = q->head->h.next;
      // Этот блок станет новой головой очереди
      // This block will be the new head of queue
      bp->h.prev = NULL;
      if ((void *)q->head < q->afirst || (void *)q->head > q->alast) {
	// in malloced list
	q->head->h.fdata = q->head->h.ffree = 0;
	q->head->h.next = q->flist;
	q->flist = q->head;
      } else {
	// in array list
	q->head->h.ffree = -1; // признак свододного блока в массиве
	if (q->head->h.next = q->aflist)
	  // !!! в массиве двусвязный список свободных блоков для очереди
	  // we use double linked list of free blocks for the queue in an array
	  q->aflist->h.prev = q->head;
	q->aflist = q->head;
      }
      q->head = bp;  // Обновим голову.  Update queue head
    }
  } else {
    q->head->h.fdata = fd;
  }
  return pr;
}

/*  
 *  merge
 *
 *  Description:
 *      This function merge of two consecutive and already sorted parts 
 *      of the array, placing the result in place of these parts
 *
 *  Parameters:
 *      a: [in/out]
 *          Sorted array
 *      q: [in/out]
 *          Queue control block
 *      l: [in]
 *          The beginning of the first merge part of the array
 *      r: [in]
 *          The beginning of the second merge part of the array
 *      rlast: [in]
 *          The end of the second merge part of the array
 *      fpcmp: [in]
 *          Comparator
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *      At least one unit must be on the queue control block free list.
 *      Make it head of the queue for the elements of the array left side.
 *      When merge is completed. move all queue malloc-blocks in the free list .
 *
 */
static void
merge (char *a, DATA_QUEUE *q, size_t l, size_t r, size_t rlast,
       int (*fpcmp)(const void *, const void *))
{
  char *pr = (char *)a+r*q->esize;
  if (fpcmp(pr,pr-q->esize) >= 0)
    return;

  Q_BLOCK *bp;

  /*
    Хотя бы один блок д.б. в списке свободных. 
    Сделаем из него очередь элементов левой части.

    At least one unit must be on the free list.
    Make it head of the queue for the elements of the array left side
  */
  bp = q->head = q->tail = q->flist;
  q->flist = q->flist->h.next;
  bp->h.prev = bp->h.next = NULL;
  q->falloc = NULL;
  q->ffree = pr;

  char *pq,          // элемент из очереди
                     // first in the queue

    *pl = a+l*q->esize,     // сюда пишем результат
                            // pointer to put result
    *pj = pr,               // элемент из головы правой части
                            // right side head item
    *pe = a+rlast*q->esize; // конец данных  end of right side

  /*
    Переносим элементы левой части в конец очереди и сливаем на их
    месте элементы из головы очереди с элементами из правой части
    массива, получая упорядоченый результат слияния
  
    Move items from the left side of the end of the queue and merge in
    their place the elements of the head of the queue with the
    elements from the right side of the array, the results in order to
    give the merger
  */
  while (pl < pr) {
    enq (q,pl,pj);
    if (fpcmp(head(q),pj) <= 0) {
      memcpy(pl,deq(q),q->esize);  // из очереди (был в левой части)
    } else {
      memcpy(pl,pj,q->esize);      // из правой части
      pj += q->esize;
    }
    pl += q->esize;
  }

  char *mergebound = pl+q->esize;
  /*
    Слияние оставшихся элементов правой части массива с очередью

    Merge the remaining elements of the right side of the array with
    elements from the queue
  */
  while (pj <= pe) { // слияние остатка правой части с очередью
    if (!(pq = (char *)head(q)))
      // Queue is empty. In this case, the end of the right side on the ground
      break;  // очередь опустела. В этом случае конец правой части на месте
    if (q->falloc) {
      // на месте элементов правой части есть блоки очереди 
      // on-site elements of the right is the  queue units
      if (mergebound > (char *)q->falloc) { 
	// переместим блок очереди в свободное место или в malloc-блок
	// move the queue unit in free right side area or in the malloc-block
	movfalc(q,pj);
	pq = (char *)head(q);
      }
      mergebound += q->esize;
    }
    if (fpcmp(pq,pj) <= 0) {
      memcpy(pl,deq(q),q->esize); // вольем из очереди
    } else {
      memcpy(pl,pj,q->esize);     // из правой части
      pj += q->esize;
    }
    pl += q->esize;
  }

  /*
    все элементы правой части заняли на свои места
    перенесем остатки очереди в конец массива

    all elements of the right side took to their seats
    transfer the remains of queue to the end of the array
  */
  while (head(q)) { // перенесем остатки очереди в конец результата
    if (q->falloc) {
      if (mergebound > (char *)q->falloc) 
	movfalc(q,pj);
      mergebound += q->esize;
    }
    memcpy(pl,deq(q),q->esize); 
    pl += q->esize;
  }

  // слияние закончено. переместим последний блок очереди в список свободных
  // merger is completed. move last queue malloc-block in the free list 
  if (bp = q->head) {
    bp->h.fdata = bp->h.ffree = 0; 
    bp->h.next = q->flist;
    q->flist = bp;
  }

#if 0
  Q_BLOCK *nxt;
  for (bp = q->head; bp; bp = nxt) {
    nxt = bp->h.next;
    if ((char *)bp > a && (char *)bp < pe) {
      fprintf (stderr,"yamsort merge internal error. queue block ptr to a[]\n");
      continue;
    }
    bp->h.fdata = bp->h.ffree = 0; 
    bp->h.next = q->flist;
    q->flist = bp;
  }
#endif

  q->head = q->tail = NULL; // просто для порядка
}

/*  
 *  swap
 *
 *  Description:
 *      This function swaps the contents of two memory areas
 *
 *  Parameters:
 *      f: [in/out]
 *          Start address first area of ​​memory
 *      t: [in/out]
 *          Start address another area of ​​memory
 *      n: [in]
 *          Size of each area in bytes
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *
 */
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

/*  
 *  insort
 *
 *  Description:
 *      This function implements the algorithm for insertion sort
 *
 *  Parameters:
 *      a: [in/out]
 *          Sorted array
 *      size: [in]
 *          The size of the array item
 *      l: [in]
 *          The first element of the array part sortable by inserts
 *      r: [in]
 *          The last element of the array part sortable by inserts
 *      fpcmp: [in]
 *          Comparator
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *
 */
static void inline
insort (char *a,     // base
	size_t size, // item size
	size_t l,    // first item in a[]
	size_t r,    // last item in a[]
	int (*fpcmp)(const void *, const void *))
{
  char *first = a + size*l, *last = a + size*r, *p, *q;

  for (p = first+size; p <= last; p+=size) {
    for (q = p; q > first; q-=size) {
      if (fpcmp(q-size,q) <= 0)
	break;
      swap (q-size,q,size);
    }
  }
}


/*  
 *  sort
 *
 *  Description:
 *      This function controls the recursive sorting algorithm
 *
 *  Parameters:
 *      a: [in/out]
 *          Sorted array
 *      q: [in]
 *          Queue control block
 *      first: [in]
 *          The first item of the array sortable in this step sequence
 *      last: [in]
 *          The last item of the array sortable in this step sequence
 *       fpcmp: [in]
 *          Comparator
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *
 */
static void
sort (char *a,  
      DATA_QUEUE *q,
      size_t first, 
      size_t last, int (*fpcmp)(const void *, const void *) )
{
  size_t  mid = (first+last) >> 1;
  if (last-first < YAMSORT_INSLIM)
    insort (a,q->esize,first,last,fpcmp); 
  else {
    sort (a,q,first,mid-1,fpcmp);
    sort (a,q,mid,last,fpcmp);
    merge (a,q,first,mid,last,fpcmp);
  }
}



/*  
 *  yamsort
 *
 *  Description:
 *      Это реализация yamsort в qsort style
 *      This function implements yamsort in qsort style
 *
 *  Parameters:
 *      base: [in/out]
 *          Array for sorting
 *      nmemb: [in]
 *          Number of items in array
 *      size:  [in]
 *          Item size
 *      fpcmp: [in]
 *          Comparator function
 *
 *  Returns:
 *      Nothing.
 *
 *  Comments:
 *
 */
void
yamsort (void *base, 
	size_t nmemb,
	size_t size, 
	 int (*fpcmp)(const void *, const void *))
{
  Q_BLOCK  *p, *pp;
  DATA_QUEUE *q = (DATA_QUEUE *)calloc(sizeof(*q),1);

  {  // sqrt32()  найден где-то в интернете  
     //           found somewhere on the Internet
    unsigned int c = 0x8000;  
    unsigned int g = 0x8000;  
    unsigned int s = nmemb;

    for(;;) {  
        if(g*g > s)  
            g ^= c;  
        c >>= 1;  
        if(c == 0)  
	  //          return g;  
	  break;
        g |= c;  
    }  
    /*
      установим размер блока очереди в элементах равным sqrt32(size)+10;
      set the queue block size is equal to the  sqrt32 (size) +10 items
    */
    q->bsize = g + 10;
  } 

  q->afirst = base;
  q->esize = size;
  q->alast = (char *)base + nmemb*size;
  q->totbsz = sizeof(QBLOCK_HDR) + q->bsize*size;
  // выделим первый блок очереди и поместим его в список свободных
  // allocate the first block of the queue and place it in the free list
  q->flist = p = (Q_BLOCK *)malloc(q->totbsz);
  p->h.prev = p->h.next = NULL;
  p->h.fdata = p->h.ffree = 0;

  sort ((char *)base,q,0,nmemb-1,fpcmp);

  // освободим все выделенные блоки очереди
  // will free all allocated queue blocks 
  for (pp = q->head; p = pp;) {
    // ну, тут их не должно быть. Well, then they should not be
    pp = p->h.next;
    free(p);
    printf ("Xa-xa-xa\n");
  }
  for (pp = q->flist; p = pp;) {
    // все они в этом списке  they are all in this list
    pp = p->h.next;
    free(p);
  }
  free(q);  // освободим последнюю память  free the memory of the last
}

