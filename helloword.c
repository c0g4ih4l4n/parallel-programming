#include <omp.h>
#include <stdio.h>
// Hello world from multithread
int main() {

    printf("%d\n%d\n", omp_get_thread_num(), omp_get_num_threads());
	#pragma omp parallel 
	// only command follow by this line is parallel
	printf("Hello from thread %d, nthreads %d\n",
		omp_get_thread_num(),
		omp_get_num_threads());
}
