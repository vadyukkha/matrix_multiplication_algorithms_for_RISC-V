#include <stdio.h>
#include <time.h>

#include "benchmarking.h"
#include "matrix_operation.h"

void matmul_naive(const int *a, const int *b, int *c, size_t row_a, size_t col_a, size_t col_b);

void general_benchmarking(double *results) {
    int tests_count = 10;
    size_t step = 15;
    for (size_t i = 1; i <= 40; i++) {
        size_t mat_size = i*step;
        double res = benchmarking(matmul_naive, tests_count, mat_size, mat_size, mat_size);
        results[i-1] = res;
    }
}

int main() {
    double* results = (double*)malloc(40 * sizeof(double));
    general_benchmarking(results);
    for (int i = 0; i < 40; i++) {
        printf("%f circles of work\n", results[i]);
    }
    free(results);
    return 0;
}