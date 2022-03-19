#!/usr/bin/env python
from __future__ import division
from mpi4py import MPI
import random
import sys

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

points_total = int(sys.argv[1])
r = 1

class Point:
    def __init__(self):
        self.x = random.uniform(0, 1)
        self.y = random.uniform(0, 1)

    def is_inside(self, r):
        return pow(self.x, 2) + pow(self.y, 2) <= r


points_inside = 0
points_per_node = points_total // size

comm.Barrier()
start = MPI.Wtime()

for i in xrange(points_per_node):
    point = Point()

    if point.is_inside(r):
        points_inside += 1
    
total_inside = comm.reduce(points_inside, op=MPI.SUM, root=0)
if rank == 0:
    result = 4 * (total_inside / points_total)
    stop = MPI.Wtime()
    time = stop - start
    
    output = "{size};{time}".format(size=size, time=time, result=result)
    print output
