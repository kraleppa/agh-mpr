make compile
clear

values=50000000,150000000,250000000

for val in ${values//,/ }
do
    for threads in {1..4}
    do
        ./main.out $threads $val >> results.csv
    done
done
