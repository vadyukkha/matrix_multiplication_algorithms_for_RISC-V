#ifndef TESTS_API_TESTS_TESTS_GENERATOR
#define TESTS_API_TESTS_TESTS_GENERATOR

#include <numeric>
#include <random>
#include <vector>

typedef std::pair<int64_t, int64_t> matrix_size_t;

std::vector<matrix_size_t> generate_tests_parametrs(size_t count = 50);

#endif  // TESTS_API_TESTS_TESTS_GENERATOR
