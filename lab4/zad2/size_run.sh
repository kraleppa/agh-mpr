#!/bin/bash -l
#SBATCH --nodes 1
#SBATCH --ntasks 12
#SBATCH --time=00:05:00
#SBATCH --partition=plgrid
#SBATCH --account=plgmpr22
make clear
make compile
rm results.csv
printf "threads;size;elements_per_bucket;fill_time;split_time;sort_time;merge_time;total_time\n" >> results.csv

values=50000,10000000,50000000

for val in ${values//,/ }
do
    for i in {1..500}
    do
        elements_per_bucket=$(( 100*i ))
        # ./main.out threads_n table_size elements_per_bucket
        ./main.out 1 $val $elements_per_bucket >> results.csv
    done
done

