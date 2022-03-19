rm results.csv
for i in {1..1000}
do
    a=$(( 100*i ))
    mpiexec -machinefile ./1node -np 2 ./send_recv_delay.py $a >> results.csv
done
