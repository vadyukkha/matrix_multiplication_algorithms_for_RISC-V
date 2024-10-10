// Copyright 2024 by Contributors
#pragma once

#ifndef INCLUDE_NAIVE
#define INCLUDE_NAIVE

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void matmul_naive(const float *a, const float *b, float *c, size_t n);

#include "../src/naive.c"

#endif  // INCLUDE_NAIVE
