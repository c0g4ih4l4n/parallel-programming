#include "find_max_array_parallel.h"
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define NUM_THREADS 4

int find_max_parallel (int * a, int size) {

    int max = 0;
    omp_set_num_threads (NUM_THREADS);

    int start_i, end_i, id, i;
    int max0 = 0, max1 = 0, max2 = 0, max3 = 0;
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
                    if (*(a + i) > max0)
                        max0 = * (a + i); 
                    break;
                case 1: 
                    if (*(a + i) > max1)
                        max1 = * (a + i); 
                    break;
                case 2: 
                    if (*(a + i) > max2)
                        max2 = * (a + i); 
                    break;
                case 3: 
                    if (*(a + i) > max3)
                        max3 = * (a + i); 
                    break;
                default: 
                    break;
            }
        }
    }

    max = get_max(get_max(max0, max1), get_max(max2, max3));
    return max;
}

int get_max (int a, int b) 
{
    return a > b ? a : b;
}


void init (int * a, int size) {
    int i;
    srand(time(NULL));   // should only be called once

    for (i = 0; i < size; i++) {
        * (a + i) = rand();
    }
}

int find_max_sequence (int * a, int size) {
    int i = 0, max = a[0];
    for (i = 0; i < size; i++) {
        if (*(a + i) > max) {
            max = * (a + i);
        }
    }
    return max;
}
