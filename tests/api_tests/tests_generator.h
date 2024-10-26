#ifndef TESTS_API_TESTS_TESTS_GENERATOR
#define TESTS_API_TESTS_TESTS_GENERATOR

#include <numeric>
#include <random>
#include <vector>

typedef std::pair<int64_t, int64_t> pll;
typedef std::vector<pll> vpll;

vpll generate_tests_pairs(size_t count = 50);

#endif  // TESTS_API_TESTS_TESTS_GENERATOR