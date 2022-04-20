#include <omp.h>
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int main(int argc, char* argv[])
{
    int size = 1000000000;
    int threads = 4;
    int buckets_n = 4;
    int max = 16;

    int interval = max/buckets_n;
    omp_set_num_threads(threads);
    srand(time(NULL));

    int *tab = calloc(size, sizeof(int));
    int ** buckets = calloc(buckets_n, sizeof(int*));
    omp_lock_t *bucket_locks = calloc(buckets_n, sizeof(omp_lock_t));
    for(int i = 0; i<buckets_n; i++){
        buckets[i] = calloc(size, sizeof(int));
        omp_init_lock(&(bucket_locks[i]));
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


    //------

    #pragma omp parallel default(shared)
    {
        int thread_num = omp_get_thread_num();
        #pragma omp for
        for(int i = 0; i < size; i++){
            // printf("\nstart: %d\n", tab[i]);
            int target_bucket = tab[i]/interval;
            // printf("target: %d", target_bucket);
            
            int target_index = bucket_tails[target_bucket];
            // printf("\nelement: %d, target_bucket: %d, target_index: %d", tab[i], target_bucket, target_index);
            omp_set_lock(&(bucket_locks[target_bucket]));
            bucket_tails[target_bucket]++;
            buckets[target_bucket][target_index] = tab[i];
            omp_unset_lock(&(bucket_locks[target_bucket]));
            // printf("\n end: %d\n", tab[i]);
        }

        // #pragma omp single
        // {
        //     for(int i = 1; i< buckets_n; i++){
        //         bucket_tails_prefix_sum[i] = bucket_tails_prefix_sum[i-1] + bucket_tails[i-1];
        //     }
        // }

        // #pragma omp for
        // for(int current_bucket = 0; current_bucket<buckets_n; current_bucket++){
        //     int current_element = bucket_tails_prefix_sum[current_bucket];
        //     for(int i = 0; i<bucket_tails[current_bucket]; i++){
        //         tab[current_element+i] = buckets[current_bucket][i];
        //     }
        // }
    }

    //------
    
    double stop = omp_get_wtime();
    printf("\nTime: %f\n", stop - start);

    // for (int i = 1; i<size; i++){
    //     if(tab[i] < tab[i-1])
    //         printf("Not sorted!!!\n");
    // }

    // for (int i = 0; i < size; i++)
    // {
    //     printf("%d ", tab[i]);
    // }

    exit(0);

    printf("\n");
    
    for(int i = 0; i<buckets_n; i++){
        for(int j = 0; j<bucket_tails[i]; j++)
        {
            printf("%d ", buckets[i][j]);
        }
        printf("\n");
        
    }



    for(int i = 0; i<buckets_n; i++){
        printf("%d ", bucket_tails[i]);
    }
    printf("\n");
    for(int i = 0; i<buckets_n; i++){
        printf("%d ", bucket_tails_prefix_sum[i]);
    }
    printf("\nBuckets:\n");



    for (int i = 0; i < size; i++)
    {
        printf("%d ", tab[i]);
    }

    return 0;
}