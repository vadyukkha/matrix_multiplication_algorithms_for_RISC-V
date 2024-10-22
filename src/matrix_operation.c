#include "../include/matrix_operation.h"

// Realization of matrix multiplication function
void __matmul__(const int *a, const int *b, int *c, size_t rows, size_t cols) {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            for (size_t k = 0; k < cols; ++k) {
                c[i * cols + j] += a[i * cols + k] * b[k * cols + j];
            }
        }
    }
}
