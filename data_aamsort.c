struct data {
  int  key;
  double d;
};

#define SORT_NAME data
#define SORT_TYPE struct data
#define SORT_CMP(x,y) ((x).key < (y).key ? -1 : ((x).key == (y).key ? 0 : 1))

/*
  make   

  data_aamsort(struct data a[], size_t n) 

  function
 */

#include "aamsort_tmpl.h"
