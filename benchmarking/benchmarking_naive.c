#include <stdio.h>
#include <time.h>

#include "benchmarking.h"
#include "matrix_operation.h"

void matmul_naive(const int *a, const int *b, int *c, size_t row_a, size_t col_a, size_t col_b);

int main() {
    int mat_size = 500;
    int tests_count = 10;
    double res =
        benchmarking(matmul_naive, tests_count, mat_size, mat_size, mat_size) / CLOCKS_PER_SEC;
    printf("%f seconds\n", res);
    return 0;
}
