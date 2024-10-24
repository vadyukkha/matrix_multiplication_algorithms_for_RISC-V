#include "matrix_operation.h"

// Realization of naive matrix multiplication function
void matmul_naive(const int *a, const int *b, int *c, size_t row, size_t col) {
    for (size_t i = 0; i < row; i++) {
        for (size_t j = 0; j < col; j++) {
            for (size_t k = 0; k < col; k++) {
                c[i * col + j] += a[i * col + k] * b[k * col + j];
            }
        }
    }
}
