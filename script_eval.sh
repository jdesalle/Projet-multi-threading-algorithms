#!/bin/bash

NTHREAD=8
RUNS=5

make producer_consumer

echo "coeurs,secondes" > data.csv

for (( i=1; i<=RUNS; i++ ))
do
	for (( n=2; n<=NTHREAD; n++ ))
	do
		output=$(/usr/bin/time -f %e ./producer_consumer $n 2>&1)
		echo $n,$output >> data.csv
	done
done

./plot_performance.py

