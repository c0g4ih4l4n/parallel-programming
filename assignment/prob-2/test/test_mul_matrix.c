#include <stddef.h>
#include "../src/mul_matrix.h"
#include "vendor/unity.h"
#include <stdlib.h>

void test_mul_matrix(void)
{
    matrix_2D * A, * B, * C, * result;
    A = (matrix_2D *) malloc (sizeof(matrix_2D));
    B = (matrix_2D *) malloc (sizeof(matrix_2D));
    C = (matrix_2D *) malloc (sizeof(matrix_2D));

    init_memory (A, 2, 2);
    init_memory (B, 2, 2);
    init_memory (C, 2, 2); 

    A->arr[0][0] = 1, A->arr[0][1] = 1, A->arr[1][0] = 1, A->arr[1][1] = 2;
    B->arr[0][0] = 2, B->arr[0][1] = -1, B->arr[1][0] = 3, B->arr[1][1] = 4;
    C->arr[0][0] = 5, C->arr[0][1] = 3, C->arr[1][0] = 8, C->arr[1][1] = 7;
    result = mul_sequence (A, B);

    int i, j;
    for (i = 0; i < 2; i++) 
        for (j = 0; j < 2; j++) 
            TEST_ASSERT_EQUAL_INT (C->arr[i][j], result->arr[i][j]);
    
}

void test_mul_matrix_parallel_col (void) 
{
    int m, n, p;
    m = 20, n = 30, p = 40;

    matrix_2D * A, * B, * C, * result;
    A = (matrix_2D *) malloc (sizeof(matrix_2D));
    B = (matrix_2D *) malloc (sizeof(matrix_2D));

    init_memory (A, m, n);
    init_memory (B, n, p);

    init_value (A);
    init_value (B);

    C = mul_parallel_col (A, B);
    result = mul_sequence (A, B);

    int i, j;
    for (i = 0; i < m; i++) 
        for (j = 0; j < p; j++) 
            TEST_ASSERT_EQUAL_INT (C->arr[i][j], result->arr[i][j]);
        
}

void test_mul_matrix_parallel (void) 
{
    int m, n, p;
    m = 20, n = 30, p = 40;

    matrix_2D * A, * B, * C, * result;
    A = (matrix_2D *) malloc (sizeof(matrix_2D));
    B = (matrix_2D *) malloc (sizeof(matrix_2D));

    init_memory (A, m, n);
    init_memory (B, n, p);

    init_value (A);
    init_value (B);

    C = mul_parallel (A, B);
    result = mul_sequence (A, B);

    int i, j;
    for (i = 0; i < m; i++) 
        for (j = 0; j < p; j++) {
            if (C->arr[i][j] ==0) 
                printf ("%d\t%d\n", i, j);
            TEST_ASSERT_EQUAL_INT (C->arr[i][j], result->arr[i][j]);
        }
        
}

int main(void) 
{
    UnityBegin("test/test_mul_matrix.c");

    RUN_TEST(test_mul_matrix);
    RUN_TEST(test_mul_matrix_parallel_col);
    RUN_TEST(test_mul_matrix_parallel);
    
    UnityEnd();
    return 0;
}
