/*
  avp 2012

  время в микросекундах

 */

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

long long
mutime()
{
  struct timeval t;
  long long mt;

#ifdef THREAD_CLOCK
  // -lrt
  struct timespec t0;

  clock_gettime(CLOCK_THREAD_CPUTIME_ID,&t0);
  mt = t0.tv_nsec/1000;
  if (t0.tv_nsec - mt*1000 > 499)
    mt++;
  mt += t0.tv_sec*1000000;
#else
  gettimeofday(&t, NULL);
  mt = (long long)t.tv_sec * 1000000 + t.tv_usec;
#endif

  return mt;
}
