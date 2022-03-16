#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int world_rank;
int world_size;

void Init(char * argv[])
{
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    if (world_size < 2) {
        fprintf(stderr, "World size must be greater than 1 for %s\n", argv[0]);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
}

void Finalize()
{
    MPI_Finalize();
}

double mpi_send_test(int how_many_ints) {
    MPI_Barrier(MPI_COMM_WORLD);
    double start,end;
    void* numbers = malloc(how_many_ints * sizeof(int));

    start = MPI_Wtime();
    if (world_rank == 0) {
        MPI_Send(numbers, how_many_ints, MPI_INT, 1, 0, MPI_COMM_WORLD);
    } else if (world_rank == 1) {
        MPI_Recv(numbers, how_many_ints, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
    end = MPI_Wtime();
    free(numbers);
    return end-start;
}
int main(int argc, char* argv[])
{
    Init(argv);
    double time;
    for(int i=1;i<100;i+=1)
    {
        time = mpi_send_test(i*1000000);
        long long bytes = i*sizeof(int)*1000000;
        if(world_rank==1)
            printf("%d %f\n",bytes ,bytes/time);
    }
    Finalize();
}