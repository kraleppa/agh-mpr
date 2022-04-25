
import csv
import matplotlib.pyplot as plt
import numpy as np 


def avg(lst):
    return sum(lst) / len(lst)

f = open('results_size_run.csv', newline='\n')
reader = csv.reader(f, delimiter=";")

fill_time_map = {}
split_time_map = {}
sort_time_map = {}
merge_time_map = {}
total_time_map = {}

next(reader)
for row in reader:
    buckets = str(row[2])
    fill_time = float(row[3])
    split_time = float(row[4])
    sort_time = float(row[5])
    merge_time = float(row[6])
    total_time = float(row[7])

    if not buckets in fill_time_map:
        fill_time_map[buckets] = [fill_time]
        split_time_map[buckets] = [split_time]
        sort_time_map[buckets] = [sort_time]
        merge_time_map[buckets] = [merge_time]
        total_time_map[buckets] = [total_time]
    if buckets in fill_time_map:
        fill_time_map[buckets] = fill_time_map[buckets] + [fill_time]
        split_time_map[buckets] = split_time_map[buckets] + [split_time]
        sort_time_map[buckets] = sort_time_map[buckets] + [sort_time]
        merge_time_map[buckets] = merge_time_map[buckets] + [merge_time]
        total_time_map[buckets] = total_time_map[buckets] + [total_time]

for key, value in fill_time_map.items():
    fill_time_map[key] = avg(value)

for key, value in split_time_map.items():
    split_time_map[key] = avg(value)

for key, value in sort_time_map.items():
    sort_time_map[key] = avg(value)

for key, value in merge_time_map.items():
    merge_time_map[key] = avg(value)

for key, value in total_time_map.items():
    total_time_map[key] = avg(value)

print(fill_time_map)
print(split_time_map)
print(sort_time_map)
print(merge_time_map)
print(total_time_map)

x = list(fill_time_map.keys())
x_tmp = np.arange(len(x))

fill_time_y = list(fill_time_map.values())
split_time_y = list(split_time_map.values())
sort_time_y = list(sort_time_map.values())
merge_time_y = list(merge_time_map.values())
total_time_y = list(total_time_map.values())


plt.bar(x_tmp - 0.2, total_time_y, 0.1, facecolor='purple', label = "Total time")
plt.bar(x_tmp - 0.1, sort_time_y, 0.1, facecolor='blue', label = "Sort time")
plt.bar(x_tmp, split_time_y, 0.1, facecolor='red', label = "Split time")
plt.bar(x_tmp + 0.1, fill_time_y, 0.1, facecolor='yellow', label = "Fill time")
plt.bar(x_tmp + 0.2, merge_time_y, 0.1, facecolor='green', label = "Merge time")




plt.xlabel('Number of buckets')
plt.ylabel('Time [s]')
plt.xticks(x_tmp, x)
plt.title('Optimal number of buckets analysis')
plt.legend()
plt.grid(True)
plt.savefig('size_run_plot.png')

