#include "matrix_operation.h"

// Realization of naive matrix multiplication function
void matmul_naive(const int *a, const int *b, int *c, size_t row_a, size_t col_a, size_t col_b) {
    for (size_t i = 0; i < row_a; i++) {
        for (size_t j = 0; j < col_b; j++) {
            for (size_t k = 0; k < col_a; k++) {
                c[i * col_b + j] += a[i * col_a + k] * b[k * col_b + j];
            }
        }
    }
}
