#!/bin/bash

g++ -std=c++11 -fopenmp -o bhatta_serial bhatta.cpp -DRESULTSFILE
g++ -std=c++11 -fopenmp -o bhatta_par_2 bhatta.cpp -DRESULTSFILE -DPARALLEL -DN_THREADS=2
g++ -std=c++11 -fopenmp -o bhatta_par_4 bhatta.cpp -DRESULTSFILE -DPARALLEL -DN_THREADS=4
g++ -std=c++11 -fopenmp -o bhatta_par_8 bhatta.cpp -DRESULTSFILE -DPARALLEL -DN_THREADS=8
g++ -std=c++11 -fopenmp -o bhatta_par_16 bhatta.cpp -DRESULTSFILE -DPARALLEL -DN_THREADS=16
g++ -std=c++11 -fopenmp -o bhatta_par_32 bhatta.cpp -DRESULTSFILE -DPARALLEL -DN_THREADS=32

declare -a versions=("bhatta_serial" "bhatta_par_2" "bhatta_par_4" "bhatta_par_8" "bhatta_par_16" "bhatta_par_32")

for version in "${versions[@]}"
do
	for file in partials/*
	do
		echo "running $version $file"
		./$version $file
	done 
done
