#!/usr/bin/env python
from __future__ import division
# from mpi4py import MPI
import random
import sys

points_total = int(sys.argv[1])
r = 1

class Point:
    def __init__(self):
        self.x = random.uniform(0, 1)
        self.y = random.uniform(0, 1)

    def is_inside(self, r):
        return pow(self.x, 2) + pow(self.y, 2) <= r


points_inside = 0

for i in xrange(points_total):
    point = Point()

    if point.is_inside(r):
        points_inside += 1
    
result = 4 * (points_inside / points_total)

print result
