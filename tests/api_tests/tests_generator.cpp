#include "tests_generator.h"

vpll generate_tests_pairs(size_t count) {
    auto generate_rnd_long = [](int64_t min = std::numeric_limits<int64_t>::min(),
                                int64_t max = std::numeric_limits<int64_t>::max()) {
        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::uniform_int_distribution<int64_t> dist(min, max);
        return dist(gen);
    };

    vpll size_matrix_pairs = {
        {0, 0},                              // Empty matrix
        {1, 1},                              // One element matrix
        {100, 100},                          // Small matrix
        {generate_rnd_long(1, 1000), 1000},  // Normal size matrix
        {INT_MAX, INT_MAX},                  // Max size
        {LONG_MIN, LONG_MIN},                // Invalid size
    };

    for (size_t i = 0; i < count; ++i) {
        int64_t rows = generate_rnd_long();
        int64_t cols = generate_rnd_long();
        size_matrix_pairs.emplace_back(rows, cols);
    }

    return size_matrix_pairs;
}
