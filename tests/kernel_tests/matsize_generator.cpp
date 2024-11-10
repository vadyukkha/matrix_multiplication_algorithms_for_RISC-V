#include "matsize_generator.h"

#include <numeric>
#include <random>

std::vector<matrix_size_t> generate_tests_parametrs(size_t count) {
    auto generate_rnd_int = [](int min = 1, int max = 500) {
        std::random_device rd;
        std::mt19937_64 gen(rd());
        std::uniform_int_distribution<int64_t> dist(min, max);
        return dist(gen);
    };

    std::vector<matrix_size_t> parametrs_size_matrix;

    for (size_t i = 0; i < count; i++) {
        int64_t row_a = generate_rnd_int();
        int64_t col_a = generate_rnd_int();
        int64_t col_b = generate_rnd_int();
        parametrs_size_matrix.emplace_back(row_a, col_a, col_b);
    }

    return parametrs_size_matrix;
}
