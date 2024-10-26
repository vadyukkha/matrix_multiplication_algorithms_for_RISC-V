#include <gtest/gtest.h>

#include "matrix_lib.h"
#include "tests_generator.h"

class test_constructors : public ::testing::TestWithParam<pll> {};

TEST_P(test_constructors, default_constructor) {
    auto [rows, cols] = GetParam();
    MatrixLib::Matrix mat;
    EXPECT_EQ(mat.getRows(), 0)
        << "Error: number of rows in the default constructor is not equal to 0";
    EXPECT_EQ(mat.getCols(), 0)
        << "Error: number of columns in the default constructor is not equal to 0";
}

TEST_P(test_constructors, main_constructor) {
    auto [rows, cols] = GetParam();

    try {
        MatrixLib::Matrix A(rows, cols);
        EXPECT_EQ(A.getRows(), rows) << "Error: number of rows does not match";
        EXPECT_EQ(A.getCols(), cols) << "Error: number of columns does not match";

        bool alloc_with_zeros = true;
        for (int64_t i = 0; i < rows; ++i) {
            for (int64_t j = 0; j < cols; ++j) {
                EXPECT_EQ(A.getElement(i, j), 0) << "Error: element is not zero";
                if (A.getElement(i, j) != 0) {
                    alloc_with_zeros = false;
                    break;
                }
            }
            if (!alloc_with_zeros) {
                break;
            }
        }
    } catch (std::invalid_argument& e) {
        EXPECT_STREQ(e.what(), "Size must be positive");
    } catch (std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "Allocation failed");
    }
}

TEST_P(test_constructors, copy_constructor) {
    auto [rows, cols] = GetParam();

    try {
        MatrixLib::Matrix A(rows, cols);
        MatrixLib::Matrix new_A_copy = A;
        EXPECT_EQ(new_A_copy.getRows(), rows)
            << "Error: number of rows does not match when copying";
        EXPECT_EQ(new_A_copy.getCols(), cols)
            << "Error: number of columns does not match when copying";

    } catch (std::invalid_argument& e) {
        EXPECT_STREQ(e.what(), "Size must be positive");
    } catch (std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "Allocation failed");
    }
}

TEST_P(test_constructors, move_constructor) {
    auto [rows, cols] = GetParam();

    try {
        MatrixLib::Matrix A(rows, cols);
        MatrixLib::Matrix new_A_move = std::move(A);
        EXPECT_EQ(new_A_move.getRows(), rows) << "Error: number of rows does not match when moving";
        EXPECT_EQ(new_A_move.getCols(), cols)
            << "Error: number of columns does not match when moving";
        EXPECT_EQ(A.getRows(), 0) << "Error: the moved matrix should be empty";
        EXPECT_EQ(A.getCols(), 0) << "Error: the moved matrix should be empty";
    } catch (std::invalid_argument& e) {
        EXPECT_STREQ(e.what(), "Size must be positive");
    } catch (std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "Allocation failed");
    }
}

INSTANTIATE_TEST_SUITE_P(test_constructors_random_sizes, test_constructors,
                         ::testing::ValuesIn(generate_tests_pairs(100)));
