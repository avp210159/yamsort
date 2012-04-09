#!/bin/sh

date


for m in 0 10 100
do
    for s in 1000 5000 10000 30000 100000 300000 1000000
    do
	./m1.sh $s $m
    done
done

for m in 0 10
do
    for s in 5000000 10000000
    do
	./m2.sh $s $m
    done
done

date



    