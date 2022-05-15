echo "Get gutenberg file"
if [ -f "gutenberg-500M.txt" ]; then
    echo "gutenberg-500M.txt already exists"
else 
    wget https://www.i3s.unice.fr/\~jplozi/hadooplab_lsds_2015/datasets/gutenberg-500M.txt.gz
    gzip -d gutenberg-500M.txt.gz 
fi

echo "Create 1GB data set"
rm -rf 1gb-set
mkdir 1gb-set
for i in {1..2}
do
    cp ./gutenberg-500M.txt ./1gb-set/$i.txt
done

echo "Create 5GB data set"
rm -rf 5gb-set
mkdir 5gb-set
for i in {1..10}
do
    cp ./gutenberg-500M.txt ./5gb-set/$i.txt
done

echo "Create 10GB data set"
rm -rf 10gb-set
mkdir 10gb-set
for i in {1..20}
do
    cp ./gutenberg-500M.txt ./10gb-set/$i.txt
done