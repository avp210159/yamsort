yamsort 

Author
------
 (c) 2012 Vasily Anishchenko (avp210159@mail.ru)

(English translation is below)

Это оглавление содержит файлы с реализацией придуманного мной
алгоритма сортировки массивов слиянием, который я назвал
yamsort (Yet Another Merge Sort).


Алгоритм обеспечивает устойчивую (stable) сортировку при использовании
небольшого количества (5-10% от размера сортируемого массива) 
динамически выделяемой памяти. Время  работы пропорционально N*log(N),
как и обычно в алгоритмах сортировки слиянием, которые в основном
используют значительный объем вспомогательной памяти в фазе слияния.


  Используем "стандартный" рекурсивный  алгоритм сортировки слиянием с
  делением  массива  пополам на  каждом  шаге.  Когда отрезок  массива
  становится маленьким (скажем короче 31) сортируем его вставками. 

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

  Подробнее о манипуляциях с очередью.

  Блок очереди - заголовок и дальше массив данных 
// Queue block header
typedef struct {
  int fdata, ffree; // индексы первого занятого и свободного элемента data[]
  struct  qblock *next, *prev;
} QBLOCK_HDR;

// Queue block with data array
typedef struct qblock {
  QBLOCK_HDR h;
  SORT_TYPE data[1];
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
    totbsz;     // размер блока очереди в байтах
} DATA_QUEUE;

  При занесении в очередь нового элемента:
  Пока в последнем блоке очереди есть место, размещаем в нем (в data[]).
  Иначе достаем новый блок и размещаем в первом элементе data[].
  Новый блок получаем следующим образом:
    1. Из списка aflist;
    2. Размещаем этот блок в свободной части массива данных;
       Это место между блоками очереди уже размещенными в массиве и
       элементами правой части, еще не перемещенными в отсортированную 
       область. Корректируем ffree.
    3. Из списка flist; 
       Это список ранее выделенных вызовом malloc() блоков, которые в 
       данный момент не содержат данные очереди.
    4. Вызываем malloc();

  При выборке элемента из очереди для помещения его в отсортированную
  последовательность проверяем, не освободился ли блок очереди.
  Если ставший пустым блок единственный в очереди, то он остается в ней
  и может повторно заполняться.
  Иначе, если блок был выделен malloc(), то помещаем его в список flist.
  Блок из области массива помечаем свободным и помещаем в список aflist.

  При занесении элемента в отсортированную последовательность, которая
  уже достигла правой части массива проверяем не занято ли это место
  началом какого-либо блока очереди или блока из списка aflist.
  Если это блок списка aflist, то он просто исключается из списка.
  Если же это блок очереди, то он копируется в свободное место. В первую
  очередь пытаемся скопировать его в свободную зону в правой части массива,
  аналогично пункту 2) в алгоритме занесения элемента в очередь. Иначе
  копируем этот блок в блок из списка flist, а если flist пуст, то вызываем
  malloc().


Файлы реализующие yamsort для C, C++.

yamsort.c  	реализация в стиле qsort функции yamsort().
yamsort.h	декларация.
yamsort_tmpl.h	реализация в стиле template C .
		семейства функций SORT_NAME_yamsort().

data_yamsort.c	генератор функции data_yamsort() из yamsort_tmpl.h
		для сортировки массива структур 
		struct data {
		  int  key;	
		  double d; }.
int_yamsort.c	генератор функции int_yamsort() из yamsort_tmpl.h
		для сортировки массива типа int.


Файлы с программами для сравнения yamsort с другими сортировками.

measure.c	вызов заданной сортировки, измерение времени ее работы
		и требуемой памяти. 
		Запущенная с флагом -h рассказывает о себе.

mutime.c	функция для получения времени в микросекундах

sort.h		скачан с  http://github.com/swenson/sort
		Christopher Swenson (chris@caswenson.com)
		Overview (из swenson-sort-3a7cb3d/README.rst)
		--------
	sort.h is an implementation a ton of sorting algorithms in C with a
	user-defined type, that is defined at include time.
	This means you don't have to pay the function call overhead of using
	standard library routine.
	You get the choice of many extra sorting routines as well, including:
	* Shell sort
	* Binary insertion sort
	* Heap sort
	* Quick sort
	* Merge sort
	* Bubble sort (ugh)
	* Tim sort
	If you don't know which one to use, you should probably use Tim sort.
	       	я использую tim_sort() и quick_sort() отсюда для сравнения 
		с yamsort.

data_sort.c	генератор функций data_tim_sort() и data_quick_sort() 
		из sort.h для сортировки массива структур 
		struct data {
		  int  key;	
		  double d; }.

int_sort.c	генератор функций int_tim_sort() и int_quick_sort() 
		из sort.h для сортировки массива типа int.

timsort.c	реализация в стиле qsort функции tim_sort из sort.h

qsort.c		_quicksort() неустойчивая быстрая сортировка
		Copyright (C) 1991,1992,1996,1997,1999,2004 
		Free Software Foundation, Inc.
		This file is part of the GNU C Library.
		Written by Douglas C. Schmidt (schmidt@ics.uci.edu).

symmsort.c	реализация в стиле qsort устойчивой сортировки слиянием
		на основе алгоритма слияния на месте, описанного 
		http://ak.hanyang.ac.kr/papers/esa2004.pdf
		Stable Minimum Storage Merging by Symmetric Comparisons
		Pok-Son Kim and Arne Kutzner.

mmsort.c	тривиальная реализация в стиле qsort устойчивой сортировки
		слиянием с дополнительной памятью N/2

aamsort_tmpl.h	реализация в стиле template C неустойчивой сортировки
		In-place Merge Sort implementation. (c)2012, Andrey Astrelin, 
		astrelin@tochka.ru 
		оригинал скачан с astr73.narod.ru/Files/msort.cpp

data_aamsort.c	генератор функции data_aamsort()
		из aamsort_tmpl.h для сортировки массива структур 
		struct data {
		  int  key;	
		  double d; }.

int_aamsort.c	генератор функции int_aamsort()
		из aamsort_tmpl.h для сортировки массива типа int.

mmsort_tmpl.h	реализация в стиле template C mmsort и symsort

data_mmsort.c	генератор функций data_mmsort() и data_symsort() 
		из mmsort_tmpl.h для сортировки массива структур 
		struct data {
		  int  key;	
		  double d; }.
int_mmsort.c	генератор функций int_mmsort() и int_symsort() 
		из mmsort_tmpl.h для сортировки массива типа int.


Файлы для проведения измерений и получения результатов.

ms.sh, m1.sh, m2.sh  shell-скрипты запуска ./measure с для замеров 
       	        времени выполнения и памяти для разных сортировок 
		с разными параметрами.
       	        
typescript-32	результаты прогона ms.sh на 32 и 64-bit Linux
typescript-64
typescript-32.64 результаты прогона ms.sh (./measure 32-bit) в 64-bit Linux

prirestab.c	программа печати результатов запуска ms.sh 
		в виде таблиц. 

restab-32	таблицы, полученные  из typescript-32, typescript-32.64 
restab-64	и typescript-64
restab-32.64


--------------------------------------

Оценки сортировок:
N - размер массива
		time		aux memory
yamsort		O(N*log(N)) ?	O(sqrt(N))	stable
tim_sort	O(N*log(N)) 	O(N/3) ?	stable
mmsort		O(N*log(N))	O(N/2) 		stable
qsort		O(N*log(N))	O(N)   		stable (unstable for huge N)
quick_sort	O(N*log(N))	O(1)		unstable
aamsort		O(N*log(N)) ?	O(1)		unstable
symmsort	O(N*(log(N))^2)	O(1)		stable

yamsort
Отношение размера динамически выделенной памяти к объему массива int []
K - количество malloc() блоков размером sqrt(N) для случайных int ключей

array N	  array байт	  queue K   queue (bytes)/array
1000  	  4000		  4	    	  0.188
5000	  20000		  6	    	  0.103
10000	  40000		  7	    	  0.081
50000	  200000	  13	    	  0.062
100000	  400000	  17	    	  0.056
250000	  1000000	  28	    	  0.058
500000	  2000000	  38		  0.055
1000000	  4000000	  55		  0.056
2500000	  10000000	  84		  0.054
5000000	  20000000	  121		  0.054
10000000  40000000	  169		  0.054
25000000  100000000	  264		  0.053


Некоторые результаты измерений для массивов int [] и 
struct data {
       int	key;
       double 	d;
} []

VmHWMi максимальная резидентная память в KBytes для int [].
timei  время сортировки int [] в миллисекундах.
Costi  "стоимость" сортировки int [] в GBytes*sec (гигобайтосекунды).
VmHWMd  максимальная резидентная память в KBytes для struct data [].
timed   время сортировки struct data [] в миллисекундах.
Costd   "стоимость" сортировки struct data [] в GBytes*sec.


		    DATA TABLES

table1 [64-bits] 1000 (4000/16000 bytes max_key_value 2147483646)
                          VmHWMi timei    Costi      VmHWMd timed    Costd   
system qsort                724    0.143      0.104    748    0.104      0.078
libc _quicksort             676    0.081      0.055    684    0.092      0.063
template yamsort            688    0.057      0.039    700    0.062      0.043
template Swenson tim_sort   688    0.057      0.039    712    0.067      0.048
template mmsort             684    0.040      0.027    700    0.046      0.032
template symmsort           672    0.098      0.066    688    0.102      0.070
template Swenson quick_so   672    0.040      0.027    684    0.044      0.030
template aamsort            680    0.052      0.035    688    0.059      0.041

table2 [64-bits] 5000 (20000/80000 bytes max_key_value 2147483646)
                          VmHWMi timei    Costi      VmHWMd timed    Costd   
system qsort                752    0.420      0.316    876    0.638      0.559
libc _quicksort             692    0.488      0.338    748    0.561      0.420
template yamsort            700    0.360      0.252    768    0.407      0.313
template Swenson tim_sort   712    0.328      0.234    800    0.380      0.304
template mmsort             704    0.247      0.174    800    0.294      0.235
template symmsort           688    0.768      0.528    748    0.819      0.613
template Swenson quick_so   688    0.244      0.168    744    0.260      0.193
template aamsort            696    0.297      0.207    748    0.346      0.259

table3 [64-bits] 10000 (40000/160000 bytes max_key_value 2147483646)
                          VmHWMi timei    Costi      VmHWMd timed    Costd   
system qsort                792    0.900      0.713   1032    1.400      1.445
libc _quicksort             708    1.050      0.743    828    1.120      0.927
template yamsort            720    0.810      0.583    856    0.920      0.788
template Swenson tim_sort   736    0.710      0.523    908    0.830      0.754
template mmsort             732    0.530      0.388    916    0.660      0.605
template symmsort           704    1.720      1.211    832    1.870      1.556
template Swenson quick_so   704    0.530      0.373    828    0.570      0.472
template aamsort            712    0.660      0.470    828    0.750      0.621

table5 [64-bits] 100000 (400000/1600000 bytes max_key_value 2147483646)
                          VmHWMi timei    Costi      VmHWMd timed    Costd   
system qsort               1496   11.400     17.054   3840   21.900     84.096
libc _quicksort            1060   12.800     13.568   2236   13.500     30.186
template yamsort           1096   10.400     11.398   2348   11.800     27.706
template Swenson tim_sort  1236    9.000     11.124   2868   11.000     31.548
template mmsort            1264    7.100      8.974   3028    8.500     25.738
template symmsort          1060   22.700     24.062   2236   24.500     54.782
template Swenson quick_so  1060    6.500      6.890   2228    7.000     15.596
template aamsort           1068    7.500      8.010   2240    8.800     19.712

table7 [64-bits] 1000000 (4000000/16000000 bytes max_key_value 2147483646)
                          VmHWMi timei    Costi      VmHWMd timed    Costd   
system qsort               8532  132.400   1129.637  31968  211.800   6770.822
libc _quicksort            4572  149.200    682.142  16296  156.400   2548.694
template yamsort           4744  130.700    620.041  17132  144.500   2475.574
template Swenson tim_sort  6124  108.200    662.617  22316  131.400   2932.322
template mmsort            6540   86.600    566.364  24124  111.000   2677.764
template symmsort          4576  279.300   1278.077  16300  319.000   5199.700
template Swenson quick_so  4576   77.200    353.267  16296   85.500   1393.308
template aamsort           4584   88.400    405.226  16300  108.700   1771.810

table23 [64-bits] 10000000 (40000000/160000000 bytes max_key_value 2147483646)
                          VmHWMi timei    Costi      VmHWMd timed    Costd   
system qsort              78804 1550.000 122146.200 313184 2606.000 816157.504
libc _quicksort           39684 1707.000  67740.588 156880 1778.000 278932.640
template yamsort          41776 1499.000  62622.224 165200 1771.000 292569.200
template Swenson tim_sort 54792 1206.000  66079.152 216912 1552.000 336647.424
template mmsort           59200 1010.000  59792.000 234984 1320.000 310178.880
template symmsort         39688 4272.000 169547.136 156884 4556.000 714763.504
template Swenson quick_so 39692  893.000  35444.956 156884 1002.000 157197.768
template aamsort          39696 1031.000  40926.576 156884 1355.000 212577.820

Несколько странные результаты для 32-bit

table1 [32-bits] 1000 (4000/12000 bytes max_key_value 2147483646)
                          VmHWMi timei    Costi      VmHWMd timed    Costd   
system qsort                620    0.117      0.073    636    0.136      0.086
template yamsort            556    0.062      0.034    556    0.084      0.047
template Swenson tim_sort   552    0.108      0.060    552    0.106      0.059
template mmsort             556    0.034      0.019    552    0.056      0.031

table2 [32-bits] 5000 (20000/60000 bytes max_key_value 2147483646)
                          VmHWMi timei    Costi      VmHWMd timed    Costd   
system qsort                640    0.679      0.435    672    0.907      0.610
template yamsort            552    0.451      0.249    552    0.514      0.284
template Swenson tim_sort   556    0.581      0.323    556    0.651      0.362
template mmsort             556    0.252      0.140    556    0.373      0.207

table5 [32-bits] 100000 (400000/1200000 bytes max_key_value 2147483646)
                          VmHWMi timei    Costi      VmHWMd timed    Costd   
system qsort               1272   19.800     25.186   2844   35.700    101.531
template yamsort            820   12.300     10.086   1872   16.800     31.450
template Swenson tim_sort  1120   17.200     19.264   2144   20.400     43.738
template mmsort            1080    8.400      9.072   2268   18.200     41.278

table7 [32-bits] 1000000 (4000000/12000000 bytes max_key_value 2147483646)
                          VmHWMi timei    Costi      VmHWMd timed    Costd   
system qsort               8220  254.400   2091.168  23952  413.100   9894.571
template yamsort           4700  169.200    795.240  12964  222.900   2889.676
template Swenson tim_sort  5876  215.100   1263.928  16732  283.400   4741.849
template mmsort            6360  115.800    736.488  18096  205.500   3718.728

table23 [32-bits] 10000000 (40000000/120000000 bytes max_key_value 2147483646)
                          VmHWMi timei    Costi      VmHWMd timed    Costd   
system qsort              78488 2952.000 231696.576 234752 4758.000 1116950.016
yamsort                   41696 4899.000 204268.704 123840 5085.000 629726.400
timsort                   54660 5305.000 289971.300 162772 6281.000 1022370.932
mmsort                    58896 3501.000 206194.896 176112 4576.000 805888.512
symmsort                  39624 8536.000 338230.464 117768 11543.000 1359396.024
libc _quicksort           39624 2604.000 103180.896 117508 2714.000 318916.712
template yamsort          41696 1978.000  82474.688 123840 2367.000 293129.280
template Swenson tim_sort 54656 1948.000 106469.888 162780 3110.000 506245.800
template mmsort           59164 1323.000  78273.972 176112 2307.000 406290.384
template symmsort         39624 5242.000 207709.008 117772 8721.000 1027089.612
template Swenson quick_so 39624 1518.000  60149.232 117768 1664.000 195965.952
template aamsort          39624 1131.000  44814.744 117768 2694.000 317266.992


=========================================
I apologize for my bad English, 
the following text is done with the help of Google Translator.

This directory contains a  files with the realization I Invented
algorithm for mergesort arrays which I call 
yamsort (Yet Another Merge Sort).

The algorithm provides a stable sort using a small amount 
(5-10% of the sorted array) dynamically allocated memory. 
Work time is proportional to N * log (N),
as usual in the merge sort algorithms, which are mainly
use a significant amount of auxiliary storage in the phase of the merger.


  Use the "standard" recursive algorithm merge sort with dividing 
  the array in half at each step. When a segment of the array becomes 
  small (say shorter than 31) apply insertion sort.

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

  More information about the manipulation of the queue.

// Queue block header
typedef struct {
  int fdata, ffree; // indexes first occupied and free element data []
  struct  qblock *next, *prev;
} QBLOCK_HDR;

// Queue block with data array
typedef struct qblock {
  QBLOCK_HDR h;
  SORT_TYPE data[1];
} Q_BLOCK;

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


  Upon adding a new element to the queue:
  While in the last block of the queue has room, place it (in the data []).
  Otherwise, we obtain a new block and place it in the first element data [].
  The new block is obtained as follows:
      1. From the list aflist;
      2. Place this block in the free part of the array data;
       	 This site between blocks queue is placed in the array and
         elements of the right-hand side, is not displaced in the sorted
         region. Adjust ffree.
      3. From the list flist;
         This is a list of previously allocated by calling malloc () blocks, 
	 which are not currently contain data queue.
      4. Call malloc ();

  When you select an item from the queue to put it in a sorted sequence,
  check to see whether the queue block will be free.
  If block become free is the only empty unit in the queue, it stays there
  and can be refilled.
  Otherwise, if the block was allocated malloc (), then put it on the 
  list flist.
  Block of the array area mark as free and put on the list aflist.

  Upon adding an item in a sorted sequence, which has reached the right side 
  of the array check whether the place is occupied by the beginning of any
  queue block or the block from the list aflist.
  If it is a block of list aflist, it is simply removed from the list.
  If a block of the queue, it is copied to free space.
  In the first all trying to copy it to a free zone on the right side 
  of the array, see item 2) in the algorithm of entry element in the queue.
  Otherwise copy this block into a block from the list flist, 
  if flist is empty, then call malloc ().


Files implementing yamsort for C, C + +.

yamsort.c 	   implementation in the style of qsort function yamsort ().
yamsort.h 	   declaration.
yamsort_tmpl.h 	   implementation style template C.
		   family of functions SORT_NAME_yamsort ().

data_yamsort.c 	   generator function data_yamsort () from yamsort_tmpl.h
		   to sort an array of structures
		   struct data {
		   	  int key;
			  double d;}.
int_yamsort.c      generator function int_yamsort () from yamsort_tmpl.h
		   to sort an array of type int.

Files with the programs to compare yamsort with other sorting.

measure.c          run a given sorting, measuring the time it works
		   and the required memory.
		   Launched with the -h flag tells about himself.

mutime.c 	   function to get time in microseconds

sort.h 		   downloaded from http://github.com/swenson/sort
		Christopher Swenson (chris@caswenson.com)
		Overview (из swenson-sort-3a7cb3d/README.rst)
		--------
	sort.h is an implementation a ton of sorting algorithms in C with a
	user-defined type, that is defined at include time.
	This means you don't have to pay the function call overhead of using
	standard library routine.
	You get the choice of many extra sorting routines as well, including:
	* Shell sort
	* Binary insertion sort
	* Heap sort
	* Quick sort
	* Merge sort
	* Bubble sort (ugh)
	* Tim sort
	If you don't know which one to use, you should probably use Tim sort.
	   I use tim_sort () and quick_sort () here for comparison
	   with yamsort.

data_sort.c 	   function generator data_tim_sort () and data_quick_sort ()
		   from sort.h to sort an array of structures
		   struct data {
		   	  int key;
			  double d;}.

int_sort.c 	   function generator int_tim_sort () and int_quick_sort ()
		   from sort.h to sort an array of type int.

qsort.c 	   _quicksort () unstable quicksort
		   Copyright (C) 1991,1992,1996,1997,1999,2004
		   Free Software Foundation, Inc.
		   This file is part of the GNU C Library.
		   Written by Douglas C. Schmidt (schmidt@ics.uci.edu).

symmsort.c 	   implementation of qsort-style stable mergesort
		   algorithm based on the merger in place, as described
		   http://ak.hanyang.ac.kr/papers/esa2004.pdf
		   Stable Minimum Storage Merging by Symmetric Comparisons
		   Pok-Son Kim and Arne Kutzner.

mmsort.c 	   trivial implementation of qsort-style stable mergesort 
		   with auxiliary memory N / 2.

aamsort_tmpl.h 	   implementation style template C unstable sorting
		   In-place Merge Sort implementation.
		   (c) 2012, Andrey Astrelin, astrelin@tochka.ru
		   downloaded from the original astr73.narod.ru/Files/msort.cpp

data_aamsort.c 	   function generator data_aamsort ()
		   from aamsort_tmpl.h to sort an array of structures
		   struct data {
		   	  int key;
			  double d;}.

int_aamsort.c 	   function generator int_aamsort ()
		   from aamsort_tmpl.h to sort an array of type int.

mmsort_tmpl.h 	   implementation in the template C style mmsort and symsort.

data_mmsort.c 	   function generator data_mmsort () and data_symsort ()
		   from mmsort_tmpl.h to sort an array of structures
		   struct data {
		   	  int key;
			  double d;}.

int_mmsort.c 	   function generator data_mmsort () and data_symsort ()
		   from mmsort_tmpl.h to sort an array of type int.


Files for measurements and results.

ms.sh, m1.sh, m2.sh   shell-script run ./measure of gauging
       	              execution time and memory usage for different sorts
		      with different parameters.
       
typescript-32	   results are run ms.sh on 32 and 64-bit Linux
typescript-64
typescript-32.64   run results ms.sh (. / measure 32-bit) in 64-bit Linux

prirestab.c 	   launch a program to print the results ms.sh
		   in tabular form.

restab-32 	   tables, derived from typescript-32, typescript-32.64
restab-64 	   and the typescript-64
restab-32.64

--------------------------------------

Estimates of sorts:
N - size of the array
		time		aux memory
yamsort		O(N*log(N)) ?	O(sqrt(N))	stable
tim_sort	O(N*log(N)) 	O(N/3) ?	stable
mmsort		O(N*log(N))	O(N/2) 		stable
qsort		O(N*log(N))	O(N)   		stable (unstable for huge N)
quick_sort	O(N*log(N))	O(1)		unstable
aamsort		O(N*log(N)) ?	O(1)		unstable
symmsort	O(N*(log(N))^2)	O(1)		stable

yamsort
The ratio of the size of dynamically allocated memory to the volume 
of the array int []
K - number of malloc () block size sqrt (N) for random int keys

array N	  array bytes	  queue K   queue (bytes)/array
1000  	  4000		  4	    	  0.188
5000	  20000		  6	    	  0.103
10000	  40000		  7	    	  0.081
50000	  200000	  13	    	  0.062
100000	  400000	  17	    	  0.056
250000	  1000000	  28	    	  0.058
500000	  2000000	  38		  0.055
1000000	  4000000	  55		  0.056
2500000	  10000000	  84		  0.054
5000000	  20000000	  121		  0.054
10000000  40000000	  169		  0.054
25000000  100000000	  264		  0.053


Some results of measurements for arrays int [], and
struct data {
        int key;
        double d;
} []

VmHWMi	maximum resident memory in KBytes for int [].
timei 	time sorting int [], in milliseconds.
Costi 	"cost" of sort int [] in GBytes * sec (gigobaytosekundy).
VmHWMd 	maximum resident memory in KBytes for struct data [].
timed 	time sorting struct data [] in milliseconds.
Costd 	"cost" sort struct data [] in GBytes * sec.

	tables with data (DATA TABLES) above...

