#include <omp.h>
 
#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char* argv[])
{
 
    int size = 16;
    int *tab = calloc(size, sizeof(int));
    // Beginning of parallel region
    #pragma omp parallel
    {
        for (int i = omp_get_thread_num(); i < size; i=i+4)
        {
            tab[i] = omp_get_thread_num();
        }
    }

    for (int i = 0; i < size; i++){
        printf("%d", tab[i]);
    }
    printf("\n"); 
    // Ending of parallel region
    return 0;
}
