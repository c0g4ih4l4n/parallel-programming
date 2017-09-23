// Description : 
// Hello world from multithread
#include <omp.h>
#include <stdio.h>
int main() {

    int threads;
    threads = 10;
    
    // set number thread of program
    omp_set_num_threads(threads);
	#pragma omp parallel 
	// only command follow by this line is parallel
    {
        int id = omp_get_thread_num();
        int thread = omp_get_num_threads();
        printf("Hello from thread %d, nthreads %d\n", id, thread);
    }
}
