#include "tests_generator.h"

std::vector<matrix_size_t> generate_tests_parametrs(size_t count) {
    auto generate_rnd_long = [](int64_t min = std::numeric_limits<int64_t>::min(),
                                int64_t max = std::numeric_limits<int64_t>::max()) {
        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::uniform_int_distribution<int64_t> dist(min, max);
        return dist(gen);
    };

    std::vector<matrix_size_t> parametrs_size_matrix = {
        {0, 0},                                                              // Empty matrix
        {1, 1},                                                              // One element matrix
        {100, 100},                                                          // Small matrix
        {generate_rnd_long(1, 1000), 1000},                                  // Normal size matrix
        {std::numeric_limits<int>::max(), std::numeric_limits<int>::max()},  // Max size
        {std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::min()},  // Invalid size
    };

    for (size_t i = 0; i < count; ++i) {
        int64_t rows = generate_rnd_long();
        int64_t cols = generate_rnd_long();
        parametrs_size_matrix.emplace_back(rows, cols);
    }

    return parametrs_size_matrix;
}
