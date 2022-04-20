CC = gcc-11 -Wall -std=c99

all:
	make clear
	make compile
	make exec

compile:
	$(CC) -fopenmp main.c -o main.out

exec:
	clear
	./main.out

clear:
	rm -f *.o *.out *.a *.so main
	clear