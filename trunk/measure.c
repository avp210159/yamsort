#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sysexits.h>


#include "yamsort.h"

struct data {
  int  d;
  double i;
};

static void
verify (int a[], int n)
{
  int  i;

  for (i = 1; i < n; i++) {
    if (a[i] < a[i-1]) {
      printf ("verify: Failure in %d\n",i);
      return;
    }
  }
  printf ("verify: OK\n");
}

static void 
fill (int a[], int n, int m)
{
  int i;
  for (i = 0; i < n; i++)
    a[i] = rand() % m;
}

// returns text of filld type
static char *
filld (struct data a[], int n, int m, int how)
{
  int i,j,k, h = 0, hw;
  long long p = 0;
  static char txthow[100];

  if ((hw = how) < 0)
    hw = -hw;

  if (hw) {
    // fill ascending or descendig and swap some keys
    if (hw > 100)
      hw = 100;
    if (hw & 1)
      h = 1;
    else
      h = 2;
    if (hw > 2)
      p = ((long long)n)*hw/100;
  }
  for (i = 0; i < n; i++) {
    switch (h) {
    case 1: // ascending 
      a[i].d = i % m;  
      break;
    case 2: // descending 
      a[i].d = (n -i) % m;
      break;
    default: //  random
      a[i].d = rand() % m;
    }
    a[i].i = i;
  }
  // !!! fix for rand() in windows (max 32767)
  long w = n/RAND_MAX + 1;

#if 0
  printf ("filld test n = %d how = %d w = %ld p = %lld hw = %d h = %d\n",
	  n,how,w,p,hw,h);
#endif

  for (i = 0; i < p; i++) {
    j = (w*rand())%n;
    k = (w*rand())%n;
    int t = a[j].d;
    a[j].d = a[k].d;
    a[k].d = t;
  }

  switch (h) {
  case 1:
    if (p)
      sprintf(txthow,"ascending  %lld keys randomly interchanged",p);
    else
      sprintf(txthow,"ascending");
    break;
  case 2:
    if (p)
      sprintf(txthow,"descending  %lld keys randomly interchanged",p);
    else
      sprintf(txthow,"descending");
    break;
  default:
    strcpy(txthow,"random");
  }

  return txthow;
}

static int
verifyd (struct data a[], int n)
{
  int  i, k = 0;

  for (i = 1; i < n; i++) {
    if (a[i].d < a[i-1].d) {
      printf ("verify: Failure in %d\n",i);
      return k;
    }
    if (a[i].d == a[i-1].d)
      if (a[i].i < a[i-1].i)
	k++;
  }
  printf ("verify: OK\n");
  return k;
}

static int
licmp (const void *a1, const void *a2)
{
  int n1 = *(int *)a1, n2 = *(int *)a2;

  return (n1 < n2)? -1: (n1 == n2)? 0: 1;
}

static int
ldcmp (const void *a1, const void *a2)
{
  struct data  *n1 = (struct data *)a1, *n2 = (struct data *)a2;

  return (n1->d < n2->d)? -1: 
    (n1->d == n2->d)? 0: 1;
}


struct sortfunc {
  char *name, type;
  void (*sort_int)();
  void (*sort_data)();
};


extern void int_yamsort(), 
  data_yamsort(), 
  timsort(),
  mmsort(),
  symmsort(),
  int_mmsort(),
  data_mmsort(),
  int_tim_sort(),
  data_tim_sort(),
  int_quick_sort(),
  data_quick_sort(),
  int_aamsort(),
  data_aamsort(),
  int_gqsort(),
  data_gqsort(),
  int_symsort(),
  asm64_intqs(),
  asm64_intrs(),
  data_symsort();

static void
quicksort (void *a, size_t nmemb, size_t size, 
	   int (*cmp)(const void *, const void *))
{
  _quicksort(a,nmemb,size,cmp,NULL);
}


static struct sortfunc flist[] = {
  {"system qsort",1,qsort,qsort},
  {"yamsort",1,yamsort,yamsort},
  {"timsort",1,timsort,timsort},
  {"mmsort",1,mmsort,mmsort},
  {"symmsort",1,symmsort,symmsort},
  {"libc _quicksort",1,quicksort,quicksort},
  {"template yamsort",0,int_yamsort,data_yamsort},
  {"template Swenson tim_sort",0,int_tim_sort,data_tim_sort},
  {"template mmsort",0,int_mmsort,data_mmsort},
  {"template symmsort",0,int_symsort,data_symsort},
  {"template Swenson quick_sort",0,int_quick_sort,data_quick_sort},
  {"template aamsort",0,int_aamsort,data_aamsort},
  {"template gnu_qsort",0,int_gqsort,data_gqsort},
  {"linasm ArrayQuickSort",0,asm64_intqs,NULL},
  {"linasm ArrayRadixSort",0,asm64_intrs,NULL},
  {NULL,0,NULL,NULL}
};
static int maxfl = sizeof(flist)/sizeof(flist[0])-1;


static char *
algnm (int n)
{
  if (n < 0 || n > maxfl)
    return "unknown";
  return flist[n].name;
}

static char *
getbits()
{
  return sizeof(void *) > 4? "64-bit":"32-bit";
}

static void
pridar (char *tit, struct data *a, int n)
{
  printf ("%s: %d\n",tit,n);
  int i;
  for (i = 0; i < n; i++) {
    printf ("{%d %d} ",a[i].d,(int)a[i].i);
  }
  printf ("\n");
}

static int
darcmp (struct data *a, struct data *b, int n)
{
  int i;
  for (i = 0; i < n; i++) {
    if (!(a[i].d == b[i].d && a[i].i == b[i].i)) {
      printf ("Check diff in %d {%d %d} {%d %d}\n",
	      i,a[i].d,(int)a[i].i,b[i].d,(int)b[i].i);
      return 1;
    }
  }
  return 0;
}

static void
prilist()
{
  printf ("List of algorithms\n");
  int i;
  for (i = 0; flist[i].name; i++) {
    printf ("%d %s [%s] ",
	     i,flist[i].name, flist[i].type ? "qsort style":"C template style");
    if (!flist[i].sort_int)
      printf ("(Not implemented for int) ");
    if (!flist[i].sort_data)
      printf ("(Not implemented for data)");
    printf ("\n");
  }
}

static int
rnd (int v, int m)
{
  int r = v/m;
  if (v%m > m/2)
    r++;
  return r;
}

// returns second field for last line selected by  'what'
static int
pri_mem (int pid, char **what)
{
  char path[1000];
  int  res = 0;

  sprintf (path,"/proc/%d/status",pid);
  FILE *in = fopen(path,"r");
  if (!in) {
    perror(path);
    return;
  }
  while (fgets(path,1000,in)) {
    char **w = what;
    while (*w) {
      if (strncasecmp(path,*w,strlen(*w)) == 0) {
	fputs(path,stdout);
	char dummy[1000];
	sscanf(path,"%s %d",dummy,&res);
	break;
      }
      w++;
    }
  }
  fclose(in);

  return res;
}

static void
usage ()
{
  char *s = 
    //"Usage: ./measure -h -l -c[NNN] -n[NNN] -d[N] -s[N] array-size rand-max
"measure sort functions   (arguments may be omitted)\n\
-h      displays this text\n\
-l      displays a list of functions\n\
-c[NNN] checks result using system qsort()\n\
        NNN - if ARRAY_SIZE less NNN then sorted arrays on check failure\n\
              will be printed\n\
-n[NNN] measures NNN [1000] times. The option -c will be ignored if -n is used\n\
-d[NNN] sorts the following array \"struct data {int k; double d;}[]\"\n\
                                   (by default sort int[])\n\
        if NNN is not defined then sort keys is generated in random order\n\
        1 - ascending  sort keys\n\
        2 - descending sort keys \n\
        3 and more - the percent of swaps in ascending (odd)\n\
                                          or descendig (even) order\n\
        field 'd' - the original index of a record\n\
-s[N]   sets number of sort function in list printed with option -l\n\
ARRAY_SIZE  Total elements for sorting (default 100000)\n\
KEY_MAX     0 : KEY_MAX-1 - range of sort key values (default RAND_MAX)\n";

  fputs(s,stdout);

}

int
main (int ac, char **av)
{
  int sortdata = 0, 
    hflag = 0,
    how = 0, 
    sort = 0, 
    loops = 0, 
    cmpres = 0, 
    checklim = 0;

  while (ac > 1 && av[1][0] == '-') {
    if (strncmp(av[1],"-h",2) == 0) {
      hflag = 1;
    Help:;
      printf ("Usage: %s -h -l -c[NNN] -n[NNN] -d[N] -s[N] ARRAY_SIZE KEY_MAX\n",
	       av[0]);
      if (hflag)
	usage();
      exit(hflag ? 0:EX_USAGE);
    }
    if (strncmp(av[1],"-l",2) == 0) {
      prilist();
      exit(0);
    }
    if (strncmp(av[1],"-d",2) == 0) {
      sortdata = 1;
      if (av[1][2])
	how = atoi(av[1]+2);
    } else  if (strncmp(av[1],"-s",2) == 0) {
      sort = atoi(av[1]+2);
    } else  if (strncmp(av[1],"-n",2) == 0) {
      if ((loops = atoi(av[1]+2)) < 2)
	loops = 1000;
    } else if (strncmp(av[1],"-c",2) == 0) { 
      cmpres = 1;
      checklim = atoi(av[1]+2);
    } else {
      printf ("Unknown flag: %s\n",av[1]);
      goto Help;
    }
    av++; ac--;
  }


  int ttf, tt, n = loops? 1000:100000, m = RAND_MAX;
  if (ac > 1)
    n = atoi(av[1]);
  if ( n <= 0)
    n = 100000;
  if (ac > 2)
    if ((m = atoi(av[2])) < 1)
      m = RAND_MAX;
  
  long long start;
  int (*cmp)(const void *, const void *);
  void (*fsort)() = NULL;
  srand(10);

  if (sortdata) {
    struct data *a;

    char *phow;
    if (sort >=0 && sort < maxfl)
      fsort = flist[sort].sort_data;
    if (fsort) {
      a = malloc(n*sizeof(*a));
      cmp = ldcmp;
      phow = filld (a,n,m,how);

      if (loops) {
	printf ("Sort (%s) struct data[] %d loops algorithm %s (%d elements (%ld bytes) %d max-value %s)\n",
		getbits(),loops,flist[sort].name,n,(long)n*sizeof(*a),m-1,phow);
	int i;
	start = mutime();
	for (i = 0; i < loops; i++) {
	  filld (a,n,m,how);
	  if (flist[sort].type)
	    fsort (a,n,sizeof(*a),cmp);
	  else
	    fsort (a,n);
	}
	tt =  rnd(mutime() - start,1000);
	char *txt = "";
	if (verifyd (a,n))
	  txt = "un";
	printf ("sort is %sstable\n",txt);
	printf ("get array fill time\n");
	start = mutime();
	for (i = 0; i < loops; i++) {
	  filld (a,n,m,how);
	}
	ttf =  rnd(mutime() - start,1000);
      } else {
	printf ("Sort (%s) struct data[] algorithm %s (%d elements (%ld bytes) %d max-value %s)\n",
		getbits(),flist[sort].name,n,(long)n*sizeof(*a),m-1,phow);

	start = mutime();
	if (flist[sort].type)
	  fsort (a,n,sizeof(*a),cmp);
	else
	  fsort (a,n);
	tt =  rnd(mutime() - start,1000);
	char *txt = "";
	if (verifyd (a,n))
	  txt = "un";
	printf ("sort is %sstable\n",txt);
	if (cmpres) {
	  printf ("sort time %d check with qsort() ... ",tt); fflush(stdout);
	  struct data *b = malloc(n*sizeof(*b));
	  srand(10);
	  filld (b,n,m,how);

	  qsort(b,n,sizeof(*b),cmp);
	  if (darcmp(a,b,n)) {
	    printf ("Invalid sort\n");
	    if (n < checklim) {
	      pridar(algnm(sort),a,n);
	      pridar("system-qsort",b,n);
	    }
	  } else  {
	    printf ("OK\n");
	  }
	}
      }
    } else {
      printf ("%d %s  UNIMPLEMENTED for data\n",
	      sort, algnm(sort));
      prilist();
      exit (EX_USAGE);
    }
  } else {  // sort int[]
    int *a;
    cmp = licmp;

    if (sort >=0 && sort < maxfl)
      fsort = flist[sort].sort_int;
    if (fsort) {
      a = malloc(n*sizeof(*a));
      fill (a,n,m);

      if (loops) {
	printf ("Sort (%s) int[] %d loops algorithm %s (%d elements (%ld bytes) %d max-value)\n",
		getbits(),loops,flist[sort].name,n,(long)n*sizeof(*a),m-1);

	int i;
	start = mutime();
	for (i = 0; i < loops; i++) {
	  fill (a,n,m);
	  if (flist[sort].type)
	    fsort (a,n,sizeof(*a),cmp);
	  else
	    fsort (a,n);
	}
	tt =  rnd(mutime() - start,1000);
	verify (a,n);
	printf ("get array fill time\n");
	start = mutime();
	for (i = 0; i < loops; i++) {
	  fill (a,n,m);
	}
	ttf =  rnd(mutime() - start,1000);
      } else {
	printf ("Sort (%s) int[] algorithm %s (%d elements (%ld bytes) %d max-value)\n",
		getbits(),flist[sort].name,n,(long)n*sizeof(*a),m-1);
	start = mutime();
	if (flist[sort].type)
	  fsort (a,n,sizeof(*a),cmp);
	else
	  fsort (a,n);
	tt = rnd(mutime() - start,1000);
	char *txt = "";
	verify (a,n);
	if (cmpres) {
	  printf ("sort time %d check with qsort() ... ",tt); fflush(stdout);
	  int *b = malloc(n*sizeof(*b));
	  srand(10);
	  fill (b,n,m);

	  qsort(b,n,sizeof(*b),cmp);
	  if (memcmp(a,b,n*sizeof(*b)))
	    printf ("Invalid sort\n");
	  else 
	    printf ("OK\n");
	}
      }
    } else {
      printf ("%d %s  UNIMPLEMENTED for int\n",
	       sort, algnm(sort));
      prilist();
      exit (EX_USAGE);
    }
  }

  fflush(stdout);
  if (loops) {
    printf ("%s: Total time sort %d fill %d msec (%f one sort cycle)\n",
	    algnm(sort),tt-ttf,ttf,(tt-ttf)/(double)loops);
  } else {
    printf ("time of %s %d msec\n",algnm(sort),tt);
  }
  char *what[] = {"vmpeak","vmhwm",NULL};
  long long vmhwm = pri_mem(getpid(),what);
  
  printf ("Cost %.3f KByte*sec (VmHwM)\n",
	  (double)vmhwm*(loops ? (tt-ttf)/(double)loops/1000:(double)tt/1000));
  exit (0);
}
