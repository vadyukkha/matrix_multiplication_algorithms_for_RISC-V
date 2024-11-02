#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "matrix_operation.h"

void matmul_naive(const int *a, const int *b, int *c, size_t row_a, size_t col_a, size_t col_b);

clock_t compare(const clock_t *a, const clock_t *b) { return (*(clock_t *)a - *(clock_t *)b); }

int main() {
    int n = 5;
    clock_t *results = (clock_t *)malloc(50 * sizeof(clock_t));
    int *a = (int *)malloc(n * n * sizeof(int));
    int *b = (int *)malloc(n * n * sizeof(int));
    int *c = (int *)calloc(n * n, sizeof(int));
    for (int i = 1; i <= n * n; i++) {
        a[i - 1] = i + 5;
        b[i - 1] = i + 3;
    }
    for (int i = 0; i < 50; i++) {
        clock_t start = clock();
        // matmul_naive(a, b, c, n, n, n);
        clock_t end = clock();
        results[i] = end - start;
    }
    // qsort(results, 50, sizeof(clock_t), compare);
    printf("%d ", (results[24] + results[25]) / 2);
    return 0;
}