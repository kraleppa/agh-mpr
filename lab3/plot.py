import matplotlib.pyplot as plt

f = open("results.csv", "r")

map = {}
for line in f:
  x = int(line)
  if not x in map:
    map[x] = 1
  else:
    map[x] += 1

x = list(map.keys())
y = list(map.values())

plt.bar(x, y, facecolor='g')
plt.xlabel('Number')
plt.ylabel('Count')
plt.title('Distribution of random generated numbers')
plt.grid(True)
plt.savefig('random.png')