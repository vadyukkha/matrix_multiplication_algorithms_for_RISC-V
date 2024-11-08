#include "benchmarking.h"

#include <limits.h>
#include <math.h>
#include <stdlib.h>

int compare(const void *a, const void *b) { return (*(double *)a - *(double *)b); }

void fillMatrixWithRandInt(int *matrix, size_t rowCount, size_t colCount) {
    for (size_t i = 0; i < rowCount; i++) {
        for (size_t j = 0; j < colCount; j++) {
            matrix[i * colCount + j] = rand() % (int)sqrt(INT_MAX);
        }
    }
}

double benchmarking(void (*matmul_func)(const int *, const int *, int *, size_t, size_t, size_t),
                    int testsCount, size_t row_a, size_t col_a, size_t col_b) {
    double *results = (double *)malloc(testsCount * sizeof(double));
    int *a = (int *)malloc(row_a * col_a * sizeof(int));
    int *b = (int *)malloc(col_a * col_b * sizeof(int));
    int *c = (int *)calloc(row_a * col_b, sizeof(int));
    fillMatrixWithRandInt(a, row_a, col_a);
    fillMatrixWithRandInt(b, col_a, col_b);

    for (int i = 0; i < testsCount; i++) {
        clock_t start = clock();
        matmul_func(a, b, c, row_a, col_a, col_b);
        clock_t end = clock();
        results[i] = (double)(end - start);
    }
    qsort(results, testsCount, sizeof(double), compare);
    if (testsCount % 2 == 0) {
        return (results[testsCount / 2 - 1] + results[testsCount / 2]) / 2.0;
    }
    return results[testsCount / 2];
}
