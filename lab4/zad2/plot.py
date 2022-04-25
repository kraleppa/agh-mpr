
import csv
f = open('teest.csv', newline='')
reader = csv.DictReader(f)
for row in reader:
    print(row['buckets'], row['total_time'])

