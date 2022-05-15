CMD="hadoop jar /usr/lib/hadoop/hadoop-streaming.jar -files mapper.py,reducer.py -mapper mapper.py -reducer reducer.py -input words -output words-output"

for size in 1 5 10
do 
    ./get_data.sh $size
    for i in {1..10}
    do
        echo "size $size iteration $i"
        ts=$(date +%s%N) ; $CMD ; tt=$((($(date +%s%N) - $ts)/1000000)) ; echo "$size;$tt" >> res.txt
    done;
    rm data.txt
done;