rm results.csv
for i in {1..12}
do
    mpiexec -machinefile nodes -np $i ./pi.py 1000000 >> results.csv
done
