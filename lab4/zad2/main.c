#include <omp.h>
 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertion_sort(int *tab, int size){
    int j, key;
    for (int i = 1; i < size; i++) {
        key = tab[i];
        j = i - 1;

        while (j >= 0 && tab[j] > key) {
            tab[j + 1] = tab[j];
            j = j - 1;
        }
        tab[j + 1] = key;
    }
}

void fill_table(int *tab, int size, int max){
    unsigned int seed = time(0) + omp_get_thread_num();
    #pragma omp for
    for(int i=0 ; i < size ; i++){
        tab[i] = rand_r(&seed) % max;
    }
}

int main(int argc, char* argv[])
{
    int threads = atoi(argv[1]);
    int size = atoi(argv[2]);
    int elements_per_bucket = atoi(argv[3]);

    int buckets_n = size/elements_per_bucket;
    int max = buckets_n;
    int interval = max/buckets_n;

    omp_set_num_threads(threads);
    srand(time(NULL));

    // create buckets
    int **buckets = calloc(buckets_n, sizeof(int*));
    for(int i = 0; i<buckets_n; i++){
        buckets[i] = calloc(elements_per_bucket * 3, sizeof(int));
    }
    
    // create lock for each bucket 
    omp_lock_t *bucket_locks = calloc(buckets_n, sizeof(omp_lock_t));
    for(int i = 0; i<buckets_n; i++){
        omp_init_lock(&(bucket_locks[i]));
    }

    // create bucket helpers
    int *bucket_tails = calloc(buckets_n, sizeof(int));
    int *bucket_tails_prefix_sum = calloc(buckets_n, sizeof(int));

    double total_start, total_end;
    total_start = omp_get_wtime();

    // create table filled with random elements
    int *tab = calloc(size, sizeof(int));
    double start, end;
    start = omp_get_wtime();
    #pragma omp parallel
    {
        fill_table(tab, size, max);
    }
    end = omp_get_wtime();
    double fill_time = end - start;

    //split elements into buckets

    start = omp_get_wtime();

    #pragma omp parallel default(shared)
    {
        #pragma omp for
        for(int i = 0; i < size; i++){
            int target_bucket = tab[i]/interval < buckets_n ? target_bucket = tab[i]/interval : buckets_n - 1;
            
            omp_set_lock(&(bucket_locks[target_bucket]));
            int target_index = bucket_tails[target_bucket];
            bucket_tails[target_bucket]++;
            buckets[target_bucket][target_index] = tab[i];
            omp_unset_lock(&(bucket_locks[target_bucket]));
        }
    }

    end = omp_get_wtime();
    double split_time = end - start;
    
    //sort each bucket
    start = omp_get_wtime();
    #pragma omp parallel default(shared)
    {
        #pragma omp for
        for(int current_bucket = 0; current_bucket<buckets_n; current_bucket++){
            insertion_sort(buckets[current_bucket], bucket_tails[current_bucket]);
        }
    }

    end = omp_get_wtime();
    double sort_time = end - start;
    
    //merge buckets
    start = omp_get_wtime();
    for(int i = 1; i< buckets_n; i++){
        bucket_tails_prefix_sum[i] = bucket_tails_prefix_sum[i-1] + bucket_tails[i-1];
    }


    #pragma omp parallel default(shared)
    {
        #pragma omp for
        for(int current_bucket = 0; current_bucket<buckets_n; current_bucket++){
            int current_element = bucket_tails_prefix_sum[current_bucket];
            for(int i = 0; i<bucket_tails[current_bucket]; i++){
                tab[current_element+i] = buckets[current_bucket][i];
            }
        }
    }

    end = omp_get_wtime();
    total_end = omp_get_wtime();
    double merge_time = end - start;

    double total_time = total_end - total_start;

    printf("%d;%f;%f;%f;%f;%f\n", threads, fill_time, split_time, sort_time, merge_time, total_time);

    for (int i = 1; i<size; i++){
        if(tab[i] < tab[i-1])
            printf("Not sorted!!!\n");
    }

    return 0;
}