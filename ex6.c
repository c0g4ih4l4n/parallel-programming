#include <stdio.h>
#include <omp.h>

#define N 10 // number of col
#define M 6 // number of row

int main() {
    
    int A[M][N], B[M][N], C[M][N];

    int i, j;

    for (i = 0; i < M; i++) {
        for (j = 0; j < N; j ++) {
            A[i][j] = i + j;
            B[i][j] = i * 2 + j * 2;
        }
    }

    int id, Sid, Eid, Nid, T = 6;

    Nid = M/T;
    omp_set_num_threads(T);
    #pragma omp parallel private (i, j, id, Sid, Eid)
    {
        id = omp_get_thread_num();
        
        Sid = Nid * id;
        Eid = Sid + Nid;

        for (i = Sid; i < Eid; i++) {
            for (j = 0; j < N; j++) {
                C[i][j] = A[i][j] + B[i][j];
            }
        }
    }

    int result = 1;
    for (i = 0; i < M; i++) {
        if (result == 0) {
            break;
        }
        for (j = 0; j < N; j++) {
            if (C[i][j] != A[i][j] + B[i][j]) {
                result = 0;
                break;
            }
        }
    }

    if (result == 1) {
        printf("True");
    } else {
        printf("False");
    }

    return 0;
}
