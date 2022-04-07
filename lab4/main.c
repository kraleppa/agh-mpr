#include <omp.h>
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int main(int argc, char* argv[])
{
 
    int size = 100;
    int *tab = calloc(size, sizeof(int));
    int threads = 1;
    int buckets_n = threads*10;
    int max = 100;
    omp_set_num_threads(threads);
    srand(time(NULL));

    double start = omp_get_wtime();

    // #pragma omp parallel
    // {
    //     int seed = time(0) + omp_get_thread_num();
    //     for (int i = omp_get_thread_num(); i < size; i=i+4)
    //     {
    //         tab[i] = rand_r(&seed) % 100;
    //     }
    // }

    #pragma omp parallel
    {
        int seed = time(0) + omp_get_thread_num();
        #pragma omp for
        for(int i=0 ; i < size ; i++){
            tab[i] = rand_r(&seed) % max;
        }
    }

    int ** buckets = calloc(buckets_n, sizeof(int*));
    for(int i = 0; i<buckets_n; i++){
        buckets[i] = calloc(size/buckets_n*2, sizeof(int));
    }
    int * bucket_tails = calloc(buckets_n, sizeof(int));

    int interval = max/buckets_n;

    for(int i = 0; i< size; i++){
        int target_bucket = tab[i]/interval;
        int target_index = bucket_tails[target_bucket];
        bucket_tails[target_bucket]++;
        buckets[target_bucket][target_index] = tab[i];
    }

    for(int i = 0; i<buckets_n; i++){
        int* current_bucket = buckets[i];
        int current_bucket_size = bucket_tails[i];
        qsort(current_bucket, current_bucket_size, sizeof(int), cmpfunc);
    }


    {
        int current_bucket = 0;
        int current_element = 0;
        for(int i = 0; i<size; i++){
            tab[i] = buckets[current_bucket][current_element++];
            if(current_element >= bucket_tails[current_bucket]){
                current_bucket++;
                current_element = 0;
            }
        }
    }

    
    double stop = omp_get_wtime();

    for(int i = 0; i<buckets_n; i++){
        for(int j = 0; j<bucket_tails[i]; j++)
        {
            printf("%d ", buckets[i][j]);
        }
        printf("\n");
        
    }

    for (int i = 0; i < size; i++)
    {
        printf("%d ", tab[i]);
    }

    printf("\nTime: %f\n", stop - start); 
    return 0;
}
