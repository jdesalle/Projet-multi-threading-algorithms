#!/bin/bash

NTHREAD=8
RUNS=5

make test_verrouTnS
echo "coeurs,secondes" > test_verrouTnS.csv
for (( i=1; i<=RUNS; i++ ))
do
	for (( n=1; n<=NTHREAD; n++ ))
	do
		output=$(/usr/bin/time -f %e ./test_verrouTnS -t $n -r 6400 2>&1)
		echo $n,$output >> test_verrouTnS.csv
	done
done

make test_verrouTnTnS
echo "coeurs,secondes" > test_verrouTnTnS.csv
for (( i=1; i<=RUNS; i++ ))
do
	for (( n=1; n<=NTHREAD; n++ ))
	do
		output=$(/usr/bin/time -f %e ./test_verrouTnTnS -t $n -r 6400 2>&1)
		echo $n,$output >> test_verrouTnTnS.csv
	done
done
./plot_performance.py test_verrouTnS test_verrouTnTnS

make philosophe
echo "coeurs,secondes" > philosophe.csv
for (( i=1; i<=RUNS; i++ ))
do
	for (( n=2; n<=NTHREAD; n++ ))
	do
		output=$(/usr/bin/time -f %e ./philosophe -t $n -r 10000 2>&1)
		echo $n,$output >> philosophe.csv
	done
done

make philosophe_spin
echo "coeurs,secondes" > philosophe_spin.csv
for (( i=1; i<=RUNS; i++ ))
do
	for (( n=2; n<=NTHREAD; n++ ))
	do
		output=$(/usr/bin/time -f %e ./philosophe_spin -t $n -r 10000 2>&1)
		echo $n,$output >> philosophe_spin.csv
	done
done
./plot_performance.py philosophe philosophe_spin

make reader_writer
echo "coeurs,secondes" > reader_writer.csv

for (( i=1; i<=RUNS; i++ ))
do
	for (( n=2; n<=NTHREAD; n++ ))
	do
		output=$(/usr/bin/time -f %e ./reader_writer -t $n 2>&1)
		echo $n,$output >> reader_writer.csv
	done
done

make reader_writer_sem
echo "coeurs,secondes" > reader_writer_sem.csv
for (( i=1; i<=RUNS; i++ ))
do
	for (( n=2; n<=NTHREAD; n++ ))
	do
		output=$(/usr/bin/time -f %e ./reader_writer_sem -t $n 2>&1)
		echo $n,$output >> reader_writer_sem.csv
	done
done
./plot_performance.py reader_writer reader_writer_sem

make producer_consumer
echo "coeurs,secondes" > producer_consumer.csv
for (( i=1; i<=RUNS; i++ ))
do
	for (( n=2; n<=NTHREAD; n++ ))
	do
		output=$(/usr/bin/time -f %e ./producer_consumer $n 2>&1)
		echo $n,$output >> producer_consumer.csv
	done
done

make producer_consumer_sem
echo "coeurs,secondes" > producer_consumer_sem.csv

for (( i=1; i<=RUNS; i++ ))
do
	for (( n=2; n<=NTHREAD; n++ ))
	do
		output=$(/usr/bin/time -f %e ./producer_consumer_sem $n 2>&1)
		echo $n,$output >> producer_consumer_sem.csv
	done
done
./plot_performance.py producer_consumer producer_consumer_sem