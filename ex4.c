// On develop
// Sum of two matrix 2 dimensions using parallel programming
#include <omp.h>
#include <stdio.h>

int main() {
    
    int n = 100;
    int a[100][100], b[100][100];
    int i, j;
    for (i = 0; i < 100; i++) {
        for (j = 0; j < 100; j++) {
            a[i] = i;
            b[i] = i*i;
        }
    }

    int result[100];
    int id, sid, eid;
    omp_set_num_threads(10);
	#pragma omp parallel private(id, sid, eid, i)
	// only command follow by this line is parallel
    {
        id = omp_get_thread_num(); 
        sid = id * (n/10);
        eid = (id + 1) * (n / 10);
        for (i = sid; i < eid; i++) {
            result[i] = a[i] + b[i];
        }
    }

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
