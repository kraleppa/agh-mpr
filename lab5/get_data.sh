echo "Get gutenberg file"
if [ -f "gutenberg-500M.txt" ]; then
    echo "gutenberg-500M.txt already exists"
else 
    wget https://www.i3s.unice.fr/\~jplozi/hadooplab_lsds_2015/datasets/gutenberg-500M.txt.gz
    gzip -d gutenberg-500M.txt.gz 
fi

times=$(($1 * 2))
hdfs dfs -rm -r words
hdfs dfs -mkdir words

for ((i=0; i<$times; i++)); do
    hadoop fs -put -f ./gutenberg-500M.txt ./words/data$i.txt
done