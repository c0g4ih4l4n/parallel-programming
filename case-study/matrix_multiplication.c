// Case study 1
// matrix multiplacation using open mpi

#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

void init_matrix(int **, int, int);
void print_matrix(int **, int, int);
int main() {

    int m, n, p;
    m = 10;
    n = 10;
    p = 10;

    int **a, **b, **c; 

    init_matrix(a, m, n);

    print_matrix(a, m, n);

    return 0;
}

void init_matrix(int ** a, int col, int row) {
    int i ,j;
    
    a = (int**) malloc (row * sizeof(int*));
    for (i = 0; i < row; i++) {
        * (a + i) = (int *) malloc(col * sizeof(int));
    }


    for (i=0; i<row; i++) {
        for (j =0; j < col; j++) {
            *(*(a + i) + j) = 1;
        }
    }
    
}

void print_matrix(int ** a, int col, int row) {
    int i, j;
    for (i = 0; i < row; i ++) {
        for (j = 0; j < col; j++) {
            printf(" %d ", *(*(a + i) + j));
        }
        printf("\n");
    }
}

        
