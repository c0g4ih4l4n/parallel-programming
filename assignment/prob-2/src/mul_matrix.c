#include "mul_matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

#define NUM_THREADS 4

#define NUM_THREADS_DEFAULT 4

#define NUM_THREAD_COL 8 

#define NUM_THREAD_ROW 4
// Parallel column only
matrix_2D * mul_parallel_col (matrix_2D * A, matrix_2D * B) {

    if (A->col != B->row) 
        return NULL;

    int num_threads;

    if (NUM_THREADS > A->col)
        num_threads = NUM_THREADS_DEFAULT;
    else 
        num_threads = NUM_THREADS;

    omp_set_num_threads (num_threads);

    matrix_2D * result;
    result = (matrix_2D *) malloc (sizeof(matrix_2D));

    init_memory (result, A->row, B->col);

    int start_i, end_i, id, i, j, k;
    
    #pragma omp parallel private(start_i, end_i, id, i, j, k)
    {
        id = omp_get_thread_num();
        
        if (id == 0) 
            start_i = 0;
        else 
            start_i = (id * result->col) / num_threads + 1;

        if (id == num_threads - 1)
            end_i = result->col - 1;
        else 
            end_i = ((id + 1) * result->col) / num_threads;

        for (i = 0; i < result->row; i++) 
            for (j = start_i; j < end_i + 1; j++) {
                result->arr[i][j] = 0;
                for (k = 0; k < A->col; k++) 
                    result->arr[i][j] += A->arr[i][k] * B->arr[k][j];
            }

    }

    return result;
}


// Parallel column and row
matrix_2D * mul_parallel (matrix_2D * A, matrix_2D * B) {

    // check condition of muliplication matrix
    if (A->col != B->row) 
        return NULL;

    int num_threads = NUM_THREAD_COL * NUM_THREAD_ROW;

    omp_set_num_threads (num_threads);

    matrix_2D * result;
    result = (matrix_2D *) malloc (sizeof(matrix_2D));

    init_memory (result, A->row, B->col);


    // private memory for parallel
    int start_i, end_i, start_j, end_j, id, i_row, j_col, i, j, k;
    
    // parallel calculate
    #pragma omp parallel private(start_i, end_i, start_j, end_j, id, i, j, k, i_row, j_col)
    {
        // cal i_row and j_col
        id = omp_get_thread_num();
        i_row = id / NUM_THREAD_COL;
        j_col = id - i_row * NUM_THREAD_COL;
        
        // set start i and end i
        if (i_row == 0) 
            start_i = 0;
        else 
            start_i = (i_row * result->row) / NUM_THREAD_ROW + 1;

        if (i_row == NUM_THREAD_ROW - 1)
            end_i = result->row - 1;
        else 
            end_i = ((i_row + 1) * result->row) / NUM_THREAD_ROW;
 
        // set start j and end j
        if (j_col == 0) 
            start_j = 0;
        else 
            start_j = (j_col * result->col) / NUM_THREAD_COL + 1;

        if (j_col == NUM_THREAD_COL - 1)
            end_j = result->col - 1;
        else 
            end_j = ((j_col + 1) * result->col) / NUM_THREAD_COL;


        // each thread id execute hcn have row (start_i, end_i) 
        // and col (start_j, end_j)
        for (i = start_i; i < end_i + 1; i++) 
            for (j = start_j; j < end_j + 1; j++) {
                result->arr[i][j] = 0;
                for (k = 0; k < A->col; k++) 
                    result->arr[i][j] += A->arr[i][k] * B->arr[k][j];
            }
    }

    return result;
}

// init random value of matrix 
void init_value (matrix_2D * A) {
    int i, j;
    srand(time(NULL));   // should only be called once

    // for faster execute
    int row = A->row, col = A->col;
    int ** arr = A->arr;

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            * (* (arr + i) + j) = rand();
        }
    }
}

// init memory for matrix
void init_memory (matrix_2D * A, int row, int col) {
    int i;
    A->row = row; A->col = col;
    A->arr = (int **) malloc (row * sizeof(int*));

    for (i = 0; i < row; i++) {
        A->arr[i] = (int *) malloc (col * sizeof(int));
    }
}



// multiplication matrix in sequence 
// for check result purpose
matrix_2D * mul_sequence (matrix_2D * A, matrix_2D * B) {
    matrix_2D * C;
    int i = 0, j = 0, k = 0;

    C = (matrix_2D *) malloc (sizeof(matrix_2D));

    init_memory (C, A->row, B->col);

    for (i = 0; i < C->row; i++) {
        for (j = 0; j < C->col; j++) {
            C->arr[i][j] = 0;
            for (k = 0; k < A->col; k++) 
                C->arr[i][j] += A->arr[i][k] * B->arr[k][j];
        }
    }
    return C;
}
