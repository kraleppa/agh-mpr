"""
Word count
"""

import collections
import sys

if __name__ == '__main__':
    path = sys.argv[1]
    counter = collections.Counter()
    with open(path, 'r', encoding='iso-8859-15') as file:
        for line in file:
            counter.update(line.split(' '))
    # print(counter)
       