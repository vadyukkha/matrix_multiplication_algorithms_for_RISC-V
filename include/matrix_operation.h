#ifndef INCLUDE_MATRIX_OPERATION_H
#define INCLUDE_MATRIX_OPERATION_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
// Declaration of naive matrix multiplication function
void matmul_naive(const int *a, const int *b, int *c, size_t row_a, size_t col_a, size_t col_b);

// Declaration of transpose matrix multiplication function
void matmul_transpose(const int *a, const int *b, int *c, size_t row_a, size_t col_a, size_t col_b);

// Declaration of block transpose matrix multiplication function
void matmul_block_transpose(const int *a, const int *b, int *c, size_t row_a, size_t col_a,
                            size_t col_b);

#ifdef RISCV
// Declaration of vectorization (RISC-V) matrix multiplication function
void matmul_vectorization(const int *a, const int *b, int *c, size_t row_a, size_t col_a,
                          size_t col_b);

// Declaration of vectorization (RISC-V) matrix multiplication function
void matmul_vectorization_asm(const int *a, const int *b, int *c, size_t row_a, size_t col_a,
                              size_t col_b);
#else
// Declaration of vectorize (x86) matrix multiplication function
void matmul_vectorize_x86(const int *a, const int *b, int *c, size_t row_a, size_t col_a,
                          size_t col_b);
#endif
}
#endif

#endif  // MATRIX_OPERATION_H
