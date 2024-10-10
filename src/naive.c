// Copyright 2024 by Contributors
#include "../include/naive.h"

void matmul_naive(const float *a, const float *b, float *c, size_t n) {
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            for (size_t k = 0; k < n; k++) {
                c[i * n + j] += a[i * n + k] * b[k * n + j];
            }
        }
    }
}
