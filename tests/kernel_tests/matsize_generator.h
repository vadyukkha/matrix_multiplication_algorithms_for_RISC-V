#ifndef TESTS_KERNEL_TESTS_MATSIZE_GENERATOR
#define TESTS_KERNEL_TESTS_MATSIZE_GENERATOR

#include <cstdint>
#include <tuple>
#include <vector>

typedef std::tuple<int64_t, int64_t, int64_t> matrix_size_t;

std::vector<matrix_size_t> generate_tests_parametrs(size_t count = 50);

#endif  // TESTS_KERNEL_TESTS_MATSIZE_GENERATOR
