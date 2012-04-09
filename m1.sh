#!/bin/sh

N=${1:-100000}
MAX=${2:--1}
REP=${3:-999}

if [ $REP = 999 ]; then
    if [ $N -lt 10000 ]; then
	REP=1000
    else
	if [ $N -lt 50000 ]; then
	    REP=100
	else
	    REP=10
	fi
    fi
fi

echo ============TEST measure algorithms N=$N MAX=$MAX REP=$REP

#exit

for i in 0 1 2 3 4 5 6 7 8 9 10 11
do
    echo +++++ s$i +++++
    if [ $i = 10 ] && [ $1 -gt 30000 ]; then
	if [ "$2" -gt 0 ] && [ "$2" -lt 10000 ]; then
	    echo Swenson quick_sort too slow for MAX=$2
	    continue
	fi
    fi

    ./measure -n$REP -s$i $1 $2 
     ./measure -n$REP -s$i -d $1 $2 
     ./measure -n$REP -s$i -d1 $1 $2 
     ./measure -n$REP -s$i -d2 $1 $2 
     ./measure -n$REP -s$i -d3 $1 $2 
     ./measure -n$REP -s$i -d4 $1 $2 
     ./measure -n$REP -s$i -d10 $1 $2 
     ./measure -n$REP -s$i -d11 $1 $2 
    echo -------------------------
done
