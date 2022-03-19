#!/bin/bash -l
#SBATCH --nodes 1
#SBATCH --ntasks 12
#SBATCH --time=12:00:00
#SBATCH --partition=plgrid
#SBATCH --account=plgmpr22

values=4000000,34641016,300000000
# values=400,3460,30000

module add plgrid/tools/openmpi
module add plgrid/libs/python-mpi4py/3.0.0-python-2.7
rm results.csv

for val in ${values//,/ }
do
    for i in {1..15}
    do
        for threads in {1..12}
        do
            mpiexec -np $threads ./pi.py $val >> results.csv
        done
    done
done
