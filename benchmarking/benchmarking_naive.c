#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matrix_operation.h"

void matmul_naive(const int *a, const int *b, int *c, size_t row_a, size_t col_a, size_t col_b);

int compare(const void *a, const void *b) { return (*(clock_t *)a - *(clock_t *)b); }

int main() {
    int matSize = 100;
    int testsCount = 100;
    clock_t *results = (clock_t *)malloc(testsCount * sizeof(clock_t));
    int *a = (int *)malloc(matSize * matSize * sizeof(int));
    int *b = (int *)malloc(matSize * matSize * sizeof(int));
    int *c = (int *)calloc(matSize * matSize, sizeof(int));
    for (int i = 1; i <= matSize * matSize; i++) {
        a[i - 1] = i + 5;
        b[i - 1] = i + 3;
    }
    for (int i = 0; i < testsCount; i++) {
        clock_t start = clock();
        matmul_naive(a, b, c, matSize, matSize, matSize);
        clock_t end = clock();
        results[i] = end - start;
    }
    qsort(results, testsCount, sizeof(clock_t), compare);
    printf("%.1f ", (results[testsCount / 2 - 1] + results[testsCount / 2]) / 2.0);
    return 0;
}