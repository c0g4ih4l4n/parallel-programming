#include <stdio.h>
#include <omp.h>

void hello() {
    printf("Hello from multithread program !!\n");

    //omp_set_num_threads(10);
    //#pragma omp parallel
    //{
    //    int id;
    //    id = omp_get_thread_num();
    //    printf("Hello from thread %d\n", id);
    //}
}


