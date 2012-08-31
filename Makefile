ifndef CFLAGS
#CFLAGS        = -Dlinux -g -DTHREAD_CLOCK
CFLAGS        = -Dlinux -O3 -DTHREAD_CLOCK
endif
LDFLAGS	      = -lrt
CC	      = gcc
ifndef ASM64
ASMFLAG		= -DNOASM 
ASMOBJ		=
else
ASMFLAG    	= -DASM64 -I./asmSort
ASMOBJ		= ./asmSort/Sort.o
endif


SHELL	      = /bin/sh

SRCS =  mutime.c measure.c int_sort.c data_sort.c \
	yamsort.c int_yamsort.c data_yamsort.c \
	int_mmsort.c data_mmsort.c \
	int_aamsort.c data_aamsort.c \
	int_gqsort.c data_gqsort.c \
	timsort.c mmsort.c \
	symmsort.c qsort.c \
	asm64_Sort.c

OBJS =  mutime.o int_sort.o data_sort.o \
	yamsort.o int_yamsort.o data_yamsort.o \
	int_mmsort.o data_mmsort.o \
	int_aamsort.o data_aamsort.o \
	int_gqsort.o data_gqsort.o \
	timsort.o mmsort.o \
	symmsort.o qsort.o \
	asm64_Sort.o


PROG = measure prirestab


all: $(PROG) 

prirestab: prirestab.c
	$(CC) $(CFLAGS)  -o $@ $< 

measure: measure.c $(OBJS) 
	$(CC) $(CFLAGS)  -o $@ $< $(OBJS) $(LDFLAGS) $(ASMOBJ)

asm64_Sort.o:	asm64_Sort.c
	$(CC) $(CFLAGS) $(ASMFLAG) -c $<


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
int_gqsort.o: gqsort_tmpl.h
data_gqsort.o: gqsort_tmpl.h
