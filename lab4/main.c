#include <omp.h>
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int main(int argc, char* argv[])
{
    int size = 10000000;
    int threads = 4;
    int buckets_n = 1000;
    int max = buckets_n * 100;
    int interval = max/buckets_n;
    omp_set_num_threads(threads);
    srand(time(NULL));

    int *tab = calloc(size, sizeof(int));
    int ** buckets = calloc(buckets_n, sizeof(int*));
    for(int i = 0; i<buckets_n; i++){
        buckets[i] = calloc(size, sizeof(int));
    }
    int * bucket_tails = calloc(buckets_n, sizeof(int));
    int * bucket_tails_prefix_sum = calloc(buckets_n, sizeof(int));

    #pragma omp parallel
    {
        unsigned int seed = time(0) + omp_get_thread_num();
        #pragma omp for
        for(int i=0 ; i < size ; i++){
            tab[i] = rand_r(&seed) % max;
        }
    }

    double start = omp_get_wtime();

    #pragma omp parallel
    {
        int thread_num = omp_get_thread_num();
        #pragma omp for
        for(int current_bucket = 0; current_bucket<buckets_n; current_bucket++){
            for(int i = 0; i< size; i++){
                int target_bucket = tab[i]/interval;
                int target_index = bucket_tails[target_bucket];
                if(target_bucket == current_bucket){
                    bucket_tails[target_bucket]++;
                    buckets[target_bucket][target_index] = tab[i];
                }       
            }

            qsort(buckets[current_bucket], bucket_tails[current_bucket], sizeof(int), cmpfunc);
        }

        #pragma omp single
        {
            for(int i = 1; i< buckets_n; i++){
                bucket_tails_prefix_sum[i] = bucket_tails_prefix_sum[i-1] + bucket_tails[i-1];
            }
        }

        #pragma omp for
        for(int current_bucket = 0; current_bucket<buckets_n; current_bucket++){
            int current_element = bucket_tails_prefix_sum[current_bucket];
            for(int i = 0; i<bucket_tails[current_bucket]; i++){
                tab[current_element+i] = buckets[current_bucket][i];
            }
        }
    }
    
    double stop = omp_get_wtime();
    printf("\nTime: %f\n", stop - start);

    for (int i = 1; i<size; i++){
        if(tab[i] < tab[i-1])
            printf("Not sorted!!!\n");
    }

    exit(0);
    
    for(int i = 0; i<buckets_n; i++){
        printf("%d ", bucket_tails[i]);
    }
    printf("\n");
    for(int i = 0; i<buckets_n; i++){
        printf("%d ", bucket_tails_prefix_sum[i]);
    }
    printf("\nBuckets:\n");

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

    return 0;
}