
import csv
import matplotlib.pyplot as plt
import numpy as np 


def avg(lst):
    return sum(lst) / len(lst)

def speedup(time_list):
    first_element = time_list[0]
    res = []
    for time in time_list:
        res.append(first_element / time)

    return res

f = open('results_run_1.csv', newline='\n')
reader = csv.reader(f, delimiter=";")

fill_time_map = {}
split_time_map = {}
sort_time_map = {}
merge_time_map = {}
total_time_map = {}

next(reader)
for row in reader:
    threads = str(row[0])
    fill_time = float(row[3])
    split_time = float(row[4])
    sort_time = float(row[5])
    merge_time = float(row[6])
    total_time = float(row[7])

    if not threads in fill_time_map:
        fill_time_map[threads] = [fill_time]
        split_time_map[threads] = [split_time]
        sort_time_map[threads] = [sort_time]
        merge_time_map[threads] = [merge_time]
        total_time_map[threads] = [total_time]
    if threads in fill_time_map:
        fill_time_map[threads] = fill_time_map[threads] + [fill_time]
        split_time_map[threads] = split_time_map[threads] + [split_time]
        sort_time_map[threads] = sort_time_map[threads] + [sort_time]
        merge_time_map[threads] = merge_time_map[threads] + [merge_time]
        total_time_map[threads] = total_time_map[threads] + [total_time]

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

fill_time_y = list(fill_time_map.values())
split_time_y = list(split_time_map.values())
sort_time_y = list(sort_time_map.values())
merge_time_y = list(merge_time_map.values())
total_time_y = list(total_time_map.values())

plt.figure(figsize=(12, 8))

plt.plot(x, total_time_y, '-o', label = "Total time")
plt.plot(x, sort_time_y, '-o', label = "Sort time")
plt.plot(x, split_time_y, '-o', label = "Split time")
plt.plot(x, fill_time_y, '-o',label = "Fill time")
plt.plot(x, merge_time_y, '-o', label = "Merge time")


plt.xlabel('Number of threads')
plt.ylabel('Time [s]')
plt.title('Time of execution of counting sort algorithm for 1e+8 problem size')
plt.legend()
plt.grid(True)
plt.savefig('run_plot_time.png')

plt.clf()

plt.figure(figsize=(12, 8))

plt.plot(x, speedup(total_time_y), '-o', label = "Total time")
plt.plot(x, speedup(sort_time_y), '-o', label = "Sort time")
plt.plot(x, speedup(split_time_y), '-o', label = "Split time")
plt.plot(x, speedup(fill_time_y), '-o',label = "Fill time")
plt.plot(x, speedup(merge_time_y), '-o', label = "Merge time")


plt.xlabel('Number of threads')
plt.ylabel('Speedup')
plt.title('Speedup of counting sort algorithm for 1e+8 problem size')
plt.legend()
plt.grid(True)
plt.savefig('run_plot_time_speedup.png')