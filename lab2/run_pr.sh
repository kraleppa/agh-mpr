rm results.csv
values=4000000,34641016,300000000
# values=400,3460,30000

for val in ${values//,/ }
do
    for i in {1..15}
    do
        for threads in {1..12}
        do
            mpiexec -machinefile nodes -np $threads ./pi.py $val >> results.csv
        done
    done
done
