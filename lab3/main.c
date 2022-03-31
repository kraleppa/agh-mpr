#include <omp.h>
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
 
int main(int argc, char* argv[])
{
    int thread_number = 4;
    int size = 100000000;
    int max = 10;

    omp_set_num_threads(thread_number);
    int *tab = calloc(size, sizeof(int));

    double start = omp_get_wtime();
    
    #pragma omp parallel
    {
        int seed = time(0) + omp_get_thread_num();
        #pragma omp for
            for(int i=0 ; i < size ; i++){
                tab[i] = rand_r(&seed) % max;
            }
    }

    double stop = omp_get_wtime();

    // for (int i = 0; i < size; i++)
    // {
    //     printf("%d ", tab[i]);
    // }

    printf("\nTime: %f\n", stop - start); 
    return 0;
}
