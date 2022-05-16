CC=gcc
CFLAGS=-march=native -Wall -O3

all: main_seq main_omp

main_seq: main_seq.c
	$(CC) $(CFLAGS) -o main_seq main_seq.c

main_omp: main_omp.c
	$(CC) $(CFLAGS) -fopenmp -o main_omp main_omp.c

clean:
	rm -f main_seq main_omp
