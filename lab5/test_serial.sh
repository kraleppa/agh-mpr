rm res.txt
for size in 1 5 10
do 
    ./get_data_serial.sh $size
    for i in {1..10}
    do
        echo "size $size iteration $i"
        ts=$(date +%s%N) ; python3 word_count.py ./get_data.sh ; tt=$((($(date +%s%N) - $ts)/1000000)) ; echo "$size;$tt" >> res.txt
    done;
    rm data.txt
done;