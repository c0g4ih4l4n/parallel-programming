// Case study 1
// matrix multiplacation using open mpi

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define m 6
#define n 6
#define p 6

void init_matrix(int *, int, int);
void print_matrix(int *, int, int);
int main() {

    int *a, *b, *c; 

    a = (int *) malloc (m * n * sizeof(int));

    init_matrix(a, b, c, m, n);

    int i, j;
    int id, starti, k, mc, nthreads, i1, i2, k1, k2, idc, idh;

    int NT = 6, NTh = 2, NTc = 3;
    int Ms, Ps;
    Ms = m/NTh;
    Ps = n/NTc;
    omp_set_num_threads(6);

    #pragma omp parallel private (id,i,j,k,i1,i2,k1,k2)
    {
        id = omp_get_thread_num();
        idh = id/NTc;
        idc = id % NTc;
        i1 = Ms*idh;
        i2 = Ms*(idh + 1);
        k1 = Ps * idc;
        k2 = Ps * (idc + 1);

        // multiplacation
        for (i=i1; i < i2; i++) {
            for (k = k1; k < k2; k++) {
                * (c + i*p + k) = 0.0;
                for (j =0; j < n; j++) {
                    *(c + i * p + k) = *(c + i*p + k) 
                        + (*(a + i * n + j)) * (*(b + j * p + k));
                }
            }
        }
    }

    // ================
    printf(" The matrix C:\n");
    print_matrix(c, m, p);

    return 0;
}

void init_matrix(int * a, int * b, int * c, int col, int row) {
    int i,j;

    for (i=0; i<row; i++) {
        for (j =0; j < col; j++) {
            *(a + i * col + j) = 1;
        }
    }
    
}

void print_matrix(int * a, int col, int row) {
    int i, j;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("\t%d\t", *(a + i * col + j));
        }
        printf("\n");
    }
}

        
