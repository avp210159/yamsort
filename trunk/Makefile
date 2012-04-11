ifndef CFLAGS
#CFLAGS        = -Dlinux -O3
CFLAGS        = -Dlinux -O3 -DTHREAD_CLOCK
endif
LDFLAGS	      = -lrt
CC	      = gcc

SHELL	      = /bin/sh

SRCS =  mutime.c measure.c int_sort.c data_sort.c \
	yamsort.c int_yamsort.c data_yamsort.c \
	int_mmsort.c data_mmsort.c \
	int_aamsort.c data_aamsort.c \
	timsort.c mmsort.c \
	ll_sort.c ll_yamsort.c \
	symmsort.c qsort.c 

OBJS =  mutime.o int_sort.o data_sort.o \
	yamsort.o int_yamsort.o data_yamsort.o \
	int_mmsort.o data_mmsort.o \
	int_aamsort.o data_aamsort.o \
	timsort.o mmsort.o \
	ll_sort.o ll_yamsort.o \
	symmsort.o qsort.o


PROG = measure prirestab


all: $(PROG) 

prirestab: prirestab.c
	$(CC) $(CFLAGS)  -o $@ $< 

measure: measure.c $(OBJS) 
	$(CC) $(CFLAGS)  -o $@ $< $(OBJS) $(LDFLAGS)

clean:;		@rm -f *.o *.exe *~ *.bak *.BAK a.out ${PROG}

depend:
	@makedepend -Y -- $(CFLAGS) -- $(SRCS) 2>/dev/null

# DO NOT DELETE

measure.o: yamsort.h
int_sort.o: sort.h
data_sort.o: sort.h
yamsort.o: yamsort.h
int_yamsort.o: yamsort_tmpl.h
data_yamsort.o: yamsort_tmpl.h
int_mmsort.o: mmsort_tmpl.h
data_mmsort.o: mmsort_tmpl.h
int_aamsort.o: aamsort_tmpl.h
data_aamsort.o: aamsort_tmpl.h
ll_sort.o: sort.h
ll_yamsort.o: yamsort_tmpl.h
