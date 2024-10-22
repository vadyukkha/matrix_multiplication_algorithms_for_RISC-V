// Copyright 2024 by Contributors

#ifndef INCLUDE_NAIVE
#define INCLUDE_NAIVE

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef __cplusplus
extern "C" {
    void matmul_naive(const float *a, const float *b, float *c, size_t n);
}
#endif

#endif  // INCLUDE_NAIVE
