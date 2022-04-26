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

for val in {1..10}
do
    for i in {5..7}
    do
        buckets1=$(( 10 ** $i ))
        buckets2=$((5 * $buckets1))
        # ./main.out threads_n table_size buckets
        # ./main.out 1 100000000 $buckets >> results.csv
        echo $buckets1
        echo $buckets2
    done
done

