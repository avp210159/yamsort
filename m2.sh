#!/bin/sh


MAX=${2:-""}
echo ============TEST measure algorithms N=$1 MAX=$2

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

    ./measure -s$i $1 $2 
    ./measure -s$i -d $1 $2 
    echo -------------------------
done
