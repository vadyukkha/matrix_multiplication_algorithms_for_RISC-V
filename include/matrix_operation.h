#ifndef INCLUDE_MATRIX_OPERATION_H
#define INCLUDE_MATRIX_OPERATION_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
// Declaration of naive matrix multiplication function
void matmul_naive(const int *a, const int *b, int *c, size_t row_a, size_t col_a, size_t col_b);
}
#endif

#endif  // MATRIX_OPERATION_H
