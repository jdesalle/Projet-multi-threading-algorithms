#!/bin/bash

NTHREAD=8
RUNS=5

echo "coeurs,secondes"

for (( i=1; i<=RUNS; i++ ))
do
	for (( n=1; n<=NTHREAD; n++ ))
	do
		make clean -s 2> /dev/null
		output=$((/usr/bin/time -f %e make -j $n -s 2>&1) | cut -d\) -f2)
		
		echo $n,${output:1}
	done
done

