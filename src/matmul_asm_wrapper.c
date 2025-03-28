#include <stdlib.h>

#include "matrix_operation.h"

// Declaration of the assembly function
void matmul(const int *a, const int *b, int *c, size_t row_a, size_t col_a, size_t col_b,
            int *b_transpose);

void matmul_vectorization_asm(const int *a, const int *b, int *c, size_t row_a, size_t col_a,
                              size_t col_b) {
    int *b_transpose = (int *)malloc(col_a * col_b * sizeof(int));

    matmul(a, b, c, row_a, col_a, col_b, b_transpose);

    free(b_transpose);
}
