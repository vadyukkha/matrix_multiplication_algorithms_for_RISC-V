#include "benchmarking_sec.h"

#include <math.h>
#include <sys/time.h>

static int compare(const void *a, const void *b) { return (*(double *)a - *(double *)b); }

static void fill_matrix_with_randint(int *matrix, size_t row, size_t col) {
    for (size_t i = 0; i < row; i++) {
        for (size_t j = 0; j < col; j++) {
            matrix[i * col + j] = rand() % 32768;
        }
    }
}

double benchmarking_sec(void (*matmul_func)(const int *, const int *, int *, size_t, size_t,
                                            size_t),
                        int tests_count, size_t row_a, size_t col_a, size_t col_b) {
    double *results = (double *)malloc(tests_count * sizeof(double));
    int *a = (int *)malloc(row_a * col_a * sizeof(int));
    int *b = (int *)malloc(col_a * col_b * sizeof(int));
    int *c = (int *)calloc(row_a * col_b, sizeof(int));

    fill_matrix_with_randint(a, row_a, col_a);
    fill_matrix_with_randint(b, col_a, col_b);
    for (int i = 0; i < tests_count; i++) {
        struct timeval start, end;
        gettimeofday(&start, NULL);
        matmul_func(a, b, c, row_a, col_a, col_b);
        gettimeofday(&end, NULL);
        results[i] = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) * 1e-6;
    }
    qsort(results, tests_count, sizeof(double), compare);
    if (tests_count % 2 == 0) {
        return (results[tests_count / 2 - 1] + results[tests_count / 2]) / 2.0;
    }
    return results[tests_count / 2];
}
