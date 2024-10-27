#include <gtest/gtest.h>

#include "matrix_lib.h"
#include "tests_generator.h"

class test_copy_and_equal : public ::testing::TestWithParam<matrix_size_t> {};

TEST_P(test_copy_and_equal, copy_and_equal) {
    auto [rows, cols] = GetParam();

    try {
        MatrixLib::Matrix mat1(rows, cols);

        for (int i = 0; i < mat1.getRows(); i++) {
            for (int j = 0; j < mat1.getCols(); j++) {
                mat1.setElement(i, j, 3);
            }
        }

        MatrixLib::Matrix mat2 = mat1.copy();

        EXPECT_EQ(mat1.isEqual(mat2), true);
    } catch (std::invalid_argument& e) {
        EXPECT_STREQ(e.what(), "Size must be positive");
    } catch (std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "Allocation failed");
    }
}

INSTANTIATE_TEST_SUITE_P(test_copy_and_equal_random_sizes, test_copy_and_equal,
                         ::testing::ValuesIn(generate_tests_parametrs(100)));
