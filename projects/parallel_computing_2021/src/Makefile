CC=gcc
MPICC=mpicc
CFLAGS=-march=native -Wall -O3

#TODO: add the following implementations: multistart_hooke_omp multistart_hooke_omp_tasks multistart_hooke_mpi multistart_hooke_mpi_omp

all: hooke hooke_omp hooke_omp_tasks hooke_mpi hooke_mpi_omp

hooke: multistart_hooke_seq.c
	$(CC) $(CFLAGS) -o multistart_hooke_seq multistart_hooke_seq.c

hooke_omp: multistart_hooke_omp.c
	$(CC) $(CFLAGS) -fopenmp -o multistart_hooke_omp multistart_hooke_omp.c

hooke_omp_tasks: multistart_hooke_omp_tasks.c
	$(CC) $(CFLAGS) -fopenmp -o multistart_hooke_omp_tasks multistart_hooke_omp_tasks.c

hooke_mpi: multistart_hooke_mpi.c
	$(MPICC) $(CFLAGS) -o multistart_hooke_mpi multistart_hooke_mpi.c

hooke_mpi_omp: multistart_hooke_mpi_omp.c
	$(MPICC) $(CFLAGS) -fopenmp -o multistart_hooke_mpi_omp multistart_hooke_mpi_omp.c

clean:
	rm -f multistart_hooke_seq \
		multistart_hooke_omp \
		multistart_hooke_omp_tasks \
		multistart_hooke_mpi \
		multistart_hooke_mpi_omp
