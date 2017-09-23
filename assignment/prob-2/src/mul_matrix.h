#ifndef MUL_MATRIX_H
#define MUL_MATRIX_H

typedef struct matrix matrix_2D;
struct matrix {
    int ** arr;
    int col;
    int row;
};
void init_memory (matrix_2D *, int, int);
void init_value (matrix_2D *);

matrix_2D * mul_sequence (matrix_2D *, matrix_2D *);
matrix_2D * mul_parallel_col (matrix_2D *, matrix_2D *);
matrix_2D * mul_parallel (matrix_2D *, matrix_2D *);

#endif
