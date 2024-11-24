#include <stdlib.h>

#ifndef BENCHMARKING_BENCHMARKING_H
#define BENCHMARKING_BENCHMARKING_H

double benchmarking(void (*matmul)(const int*, const int*, int*, size_t, size_t, size_t),
                    int tests_count, size_t row_a, size_t col_a, size_t col_b);

#endif  // BENCHMARKING_BENCHMARKING_H
