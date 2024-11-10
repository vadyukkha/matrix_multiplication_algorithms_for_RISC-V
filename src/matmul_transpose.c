#include <stdlib.h>

#include "matrix_operation.h"

// Realization of transpose matrix multiplication function
void matmul_transpose(const int *a, const int *b, int *c, size_t row_a, size_t col_a,
                      size_t col_b) {
    int *b_transpose = (int *)malloc(col_a * col_b * sizeof(int));
    for (size_t i = 0; i < col_a; i++) {
        for (size_t j = 0; j < col_b; j++) {
            b_transpose[i * col_b + j] = b[j * col_b + i];
        }
    }

    for (size_t i = 0; i < row_a; i++) {
        for (size_t j = 0; j < col_b; j++) {
            for (size_t k = 0; k < col_a; k++) {
                c[i * col_b + j] += a[i * col_a + k] * b_transpose[j * col_b + k];
            }
        }
    }
}
