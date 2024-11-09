#include <time.h>

double benchmarking(void (*matmul)(const int*, const int*, int*, size_t, size_t, size_t),
                    int tests_count, size_t row_a, size_t col_a, size_t col_b);
