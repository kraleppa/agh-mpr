#!/usr/bin/env python
from mpi4py import MPI
import sys

comm = MPI.COMM_WORLD
rank = comm.Get_rank()

test_count = 10000
bytes_to_send = int(sys.argv[1])
message = "A" * bytes_to_send

def ping_pong():
   comm.Barrier()
   start = MPI.Wtime()

   if rank == 0:
      comm.send(message, dest=1)
      comm.recv(source=1)
   elif rank == 1:
      data = comm.recv(source=0)
      comm.send(data, dest=0)

   stop = MPI.Wtime()
   
   return stop - start




summed_time = 0

for i in range(test_count):
   time = ping_pong()
   summed_time = summed_time + time

if rank == 0:
   result = summed_time / test_count
   speed_in_mega_bits = (bytes_to_send * 8 / result) / 1000000


   # print "Time per message:", result, "s"
   # print "Message size:", bytes_to_send, "B"
   # print "Speed:", speed_in_mega_bits, "Mb/s" 

   output = "{speed};{bytes}".format(speed=speed_in_mega_bits, bytes=bytes_to_send)

   print output
