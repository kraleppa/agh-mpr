CC = gcc -Wall

all:
	make clear
	make compile
	make exec

compile:
	$(CC) -fopenmp main.c -o main.out

exec:
	clear
	./main

clear:
	rm -f *.o *.out *.a *.so main
	clear