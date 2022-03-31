#include <omp.h>
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdlib.h>
 
int main(int argc, char* argv[])
{
    int thread_number = 4;
    omp_set_num_threads(thread_number);
    int size = 16;
    int *tab = calloc(size, sizeof(int));

    double start = omp_get_wtime();
    
    #pragma omp parallel
    {
        #pragma omp for schedule(static, 1)
            for(int i=0 ; i < size ; i++){
                tab[i] = omp_get_thread_num();
            }
    }

    double stop = omp_get_wtime();

    for (int i = 0; i < size; i++)
    {
        printf("%d", tab[i]);
    }

    printf("\nTime: %f\n", stop - start); 
    return 0;
}



    // #pragma omp parallel
    // {
    //     #pragma omp for schedule(static)
    //         for(int i=0 ; i < size ; i++){
    //             tab[i] = omp_get_thread_num();
    //         }
    // }