#include <stdio.h>
#include <stdlib.h>

#include "benchmarking.h"
#include "matrix_operation.h"

void matmul_naive(const int *a, const int *b, int *c, size_t row_a, size_t col_a, size_t col_b);

int main() {
    int matSize = 500;
    int testsCount = 10;
    double res = benchmarking(matmul_naive, testsCount, matSize, matSize, matSize) / CLOCKS_PER_SEC;
    printf("%f\n", res);
    return 0;
}
