// Solution 2
#include <omp.h>
#include <stdio.h>
int main() {
    
    int n = 100;
    int a[100], b[100];
    int i;
    for (i = 0; i < 100; i++) {
        a[i] = i;
        b[i] = i*i;
    }

    int result[100];
    int id;
    omp_set_num_threads(10);
	#pragma omp parallel private(id, i)
	// only command follow by this line is parallel
    {
        id = omp_get_thread_num(); 
        for (i = 0; i < 10; i++) {
            int j = 10 * i + id;
            result[j] = a[j] + b[j];
        }
    }

    // Check result
    for (i = 0 ; i< 100; i++) {
        if (result[i] == i*i + i) {
            continue;
        } else {
            printf("False");
            break;
        }
    }
    
    if (i == 100) {
        printf("True");
    }

}
