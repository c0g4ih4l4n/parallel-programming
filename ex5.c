#include <stdio.h>
#include <malloc.h>
#include <omp.h>


int main() {
    const int N = 100;
    const int T = 100;
    int a[N], max;

    int i;
    for (i = 0; i < N; i++) {
        a[i] = -i * i + 100 * i + 4;
    }

    max = a[0];
    
    int id;
    omp_set_num_threads(T);
    #pragma omp parallel private(id)
    {
        id = omp_get_thread_num();
        if (a[id] > max) {
            max = a[id];
        }
    }

    int max_real = a[0];

    for (i = 0; i < N; i++) {
        if (a[i] > max_real) {
            max_real = a[i];
        }
    }

    if (max_real == max) {
        printf("True");
    }
    printf("%d - %d", max, max_real);
    return 0;
}

