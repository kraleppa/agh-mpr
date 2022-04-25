#!/bin/bash -l
#SBATCH --nodes 1
#SBATCH --ntasks 12
#SBATCH --time=00:05:00
#SBATCH --partition=plgrid
#SBATCH --account=plgmpr22
make clear
make compile
rm results.csv
printf "threads;size;buckets;fill_time;split_time;sort_time;merge_time;total_time\n" >> results.csv

for threads in {1..10}
do
    for threads in {1..8}
    do
        #./main.out threads_n table_size buckets
        ./main.out $threads 100000000 10000000 >> results.csv
    done
done
