#ifndef INCLUDE_MATRIX_OPERATION_H
#define INCLUDE_MATRIX_OPERATION_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
    // Declaration of naive matrix multiplication function
    void matmul_naive(const int *a, const int *b, int *c, size_t row, size_t col);
}
#endif

#endif // MATRIX_OPERATION_H
