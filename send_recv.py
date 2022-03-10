#!/usr/bin/env python
from mpi4py import MPI
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
print("elo")

if rank == 0:
   print("rank0")
   data = ('abc',123)
   comm.send(data, dest=1)
elif rank == 1:
   print("rank1")
   data = comm.recv(source=0)
   print(data)
else:
   print("Expected only two nodes")