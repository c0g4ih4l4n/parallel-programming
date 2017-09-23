#include "sum_array_parallel.h"
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define NUM_THREADS 4

int sum_parallel (int * a, int size) {

    int sum = 0;
    omp_set_num_threads (NUM_THREADS);

    int start_i, end_i, id, i;
    int sum0 = 0, sum1 = 0, sum2 = 0, sum3 = 0;
    #pragma omp parallel private(start_i, end_i, id, i)
    {
        id = omp_get_thread_num();

        if (id == 0)
            start_i = 0;
        else
            start_i = (id * size) / 4 + 1;

        if (id == 3) 
            end_i = size - 1;
        else 
            end_i = ((id + 1) * size) / 4;

        for (i = start_i; i < end_i + 1; i++) {
            switch (id) {
                case 0: 
                    sum0 += * (a + i); break;
                case 1: 
                    sum1 += * (a + i); break;
                case 2: 
                    sum2 += * (a + i); break;
                case 3: 
                    sum3 += * (a + i); break;
                default: 
                    break;
            }
        }
    }

    sum = sum0 + sum1 + sum2 + sum3;
    return sum;
}


void init (int * a, int size) {
    int i;
    srand(time(NULL));   // should only be called once

    for (i = 0; i < size; i++) {
        * (a + i) = rand();
    }
}

int sum_sequence (int * a, int size) {
    int i = 0, sum = 0;
    for (i = 0; i < size; i++) {
        sum += * (a + i);
    }
    return sum;
}
