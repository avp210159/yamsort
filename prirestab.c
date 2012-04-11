#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int line = 0, table = 0;

static void
error (int code, int i, int j)
{
  printf ("ERROR line %d table%d code %d[%d][%d]\n",line, table, code,i,j);
  exit(1);
}

struct d {
  char *type;
  int  swapk, vm;
  double cost, tt;
};

struct a {
  struct d data[7];
  char *name;
  int ds, intvm;
  double intt,  intcost;
};

static struct a alg[12];
static int intbytes, databytes, elements, bits, maxval;

static void 
Fgets (char *str, int code, int i, int j, char *ver)
{
  if (!fgets(str,1000,stdin))
    error(code,i,j);
  line++;
  if (ver && *ver)
    if (strncmp(str,ver,strlen(ver)))
      error(code,i,j);
}

static char *
getaname (char *s)
{
  static char buf[100];
  char *p = strchr(s,'(');
  if (!p)
    return "???";
  strncpy(buf,s,p-s-1);
  buf[p-s-1] = 0;
  return buf;
}


static int
Getalgdata(char *str, struct a *a)
{
  char *p = strchr(str,'(');
  if (!p) {
    a->intvm = 0;
    return 0;
  }
  bits = atoi(p+1);
  if (!(p = strstr(p,"algorithm ")))
    return 0;
  p += 10;
  a->name = strdup(getaname(p));
  if (!(p = strrchr(p+strlen(a->name)+3,'(')))
    return 0;
  sscanf(p+1,"%d",&intbytes);
  sscanf(strchr(p,')')+1,"%d",&maxval);
  return 1;
}

static double
Getrightnum (char *s)
{
  char *p = s+strlen(s);

  while (!isdigit(*p))
    p--;
  while (isdigit(*p))
    p--;
  return atof(p);
}

main ()
{
  // читаем ===TEST measure algorithms N=10000 MAX=0 REP=100...
  char str[1000];
  char f1[200], f2[200], f3[200], f4[200];
  int M, R;
  char *p;



  while (fgets(str,1000,stdin))  {
    line++;
    if (strncmp(str,"====",4))
      continue;
    if (!(p = strchr(str,'N')))
      error(1,-1,-1);
    sscanf(p,"%s %s %s",f1,f2,f3);
    elements = atoi(f1+2);
    M = atoi(f2+2);
    R = atoi(f3+2);
    table++;

    // цикл по 12 алгоритмам
    int i, j;
    for (i = 0; i < 12; i++) {
      Fgets(str,2,i,-1,"+++++"); // ++++
      Fgets(str,3,i,-1,"");    // Sort ... int[]
      if (!Getalgdata(str,&alg[i])) // set intbytes, name, maxval
	continue;
      Fgets(str,4,i,-1,""); // verify
      Fgets(str,5,i,-1,""); 
      if (strncmp(str,"time ",5)) { // get array ...
	Fgets(str,6,i,-1,""); // ALG-NAME: ...(TTT ...
	alg[i].intt = atof(strchr(str,'(')+1);
      } else {
	//	sscanf(str,"%s %s %s %s %lf",f1,f2,f3,f4,&alg[i].intt);
	alg[i].intt = Getrightnum(str);
      } 
      Fgets(str,7,i,-1,""); // VmPeak
      Fgets(str,8,i,-1,""); // VmHWM
      alg[i].intvm = atoi(strchr(str,':')+1);
      Fgets(str,9,i,-1,""); // Cost
      sscanf(str,"%s %lf",f1,&alg[i].intcost);

      // цикл по измерениям data[]
      int brflag = 0;
      for (j = 0; j < 7; j++) {
	Fgets(str,10,i,j,""); // Sort
	if (str[0] == '-') {
	  brflag = 1;
	  break;
	}
	p = strchr(strchr(strchr(str,']'),'(')+1,'(')+1;
	databytes = atoi(p);
	// выберем слова о типе измерения
	p = strchr(strchr(str,']'),')')+1;
	int k = sscanf(p,"%s %s %s %s",f1,f2,f3,f4);
	if (k == 3) {
	  alg[i].data[j].swapk = 0;
	  f3[strlen(f3)-1] = 0; // delete )
	} else {
	  alg[i].data[j].swapk = atoi(f4);
	}
	alg[i].data[j].type = strdup(f3);

	Fgets(str,11,i,j,""); // verify
	Fgets(str,12,i,j,""); // sort is
	Fgets(str,13,i,j,""); // get array ...
	if (str[0] == 'g') {
	  Fgets(str,14,i,j,""); // ALG-NAME: ...(TTT ...
	  alg[i].data[j].tt = atof(strchr(str,'(')+1);
	} else {
	  alg[i].data[j].tt = Getrightnum(str);
	}
	Fgets(str,15,i,j,""); // VmPeak
	Fgets(str,16,i,j,""); // VmHWM
	alg[i].data[j].vm = atoi(strchr(str,':')+1);
	Fgets(str,17,i,j,""); // Cost
	sscanf(str,"%s %lf",f1,&alg[i].data[j].cost);
      }
      if (brflag)
	j--;
      else
	if (!fgets(str,1000,stdin)) error(18,i,-1); // -------
      alg[i].ds = j;
    }

    // печать таблиц
    printf ("table%d [%d-bits] %d (%d/%d bytes max_key_value %d)\n",
	    table,bits,elements,intbytes,databytes,maxval);
    printf ("%25s %-6s %-8s %-10s %-6s %-8s %-8s\n",
	    " ","VmHWMi","timei","Costi", "VmHWMd","timed","Costd");
    for (i = 0; i < 12; i++) {
      char name[100];
      
      strcpy(name,alg[i].name);
      name[25] = 0;
      if (alg[i].intvm)
	printf ("%-25s%6d %8.3f %10.3f %6d %8.3f %10.3f\n",
		name, 
		alg[i].intvm, alg[i].intt, alg[i].intcost,
		alg[i].data[0].vm, alg[i].data[0].tt, alg[i].data[0].cost);
      else
	printf ("%-25s not executed\n",alg[i].name);
    }
    printf ("\n");

    if (alg[0].ds > 1) {
      printf ("data[] (rand swap)    yamsort   tim_sort   mmsort   symmsort quick_sort aamsort\n");
      for (i = 0; i < alg[0].ds; i++) {
	if (alg[0].data[i].swapk == 0)
	  printf ("%-20s",alg[0].data[i].type);
	else {
	  char s[10]; sprintf(s,"(%d)",alg[0].data[i].swapk);
	  printf ("%-11s %-8s",alg[0].data[i].type,s);
	}
	for (j = 6; j < 12; j++) {
	  if (alg[j].intvm)
	    printf ("%8.3f  ",alg[j].data[i].tt);
	  else
	    printf (" no data  ");
	}
	printf ("\n");
      }
      printf ("\n");
    }
    
  }

  exit(0);
}
