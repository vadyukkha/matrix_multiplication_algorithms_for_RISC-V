#include <gtest/gtest.h>

#include "matrix_lib.h"
#include "tests_generator.h"

class test_constructors : public ::testing::TestWithParam<matrix_size_t> {};

TEST_P(test_constructors, default_constructor) {
    matrix_size_t size = GetParam();
    size_t rows = size.first;
    size_t cols = size.second;

    MatrixLib::Matrix mat;
    EXPECT_EQ(mat.getRowsSize(), 0)
        << "Error: number of rows in the default constructor is not equal to 0";
    EXPECT_EQ(mat.getColsSize(), 0)
        << "Error: number of columns in the default constructor is not equal to 0";
}

TEST_P(test_constructors, main_constructor) {
    matrix_size_t size = GetParam();
    size_t rows = size.first;
    size_t cols = size.second;

    try {
        MatrixLib::Matrix A(rows, cols);
        EXPECT_EQ(A.getRowsSize(), rows) << "Error: number of rows does not match";
        EXPECT_EQ(A.getColsSize(), cols) << "Error: number of columns does not match";

        bool alloc_with_zeros = true;
        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
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
    matrix_size_t size = GetParam();
    size_t rows = size.first;
    size_t cols = size.second;

    try {
        MatrixLib::Matrix A(rows, cols);
        MatrixLib::Matrix new_A_copy = A;
        EXPECT_EQ(new_A_copy.getRowsSize(), rows)
            << "Error: number of rows does not match when copying";
        EXPECT_EQ(new_A_copy.getColsSize(), cols)
            << "Error: number of columns does not match when copying";

    } catch (std::invalid_argument& e) {
        EXPECT_STREQ(e.what(), "Size must be positive");
    } catch (std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "Allocation failed");
    }
}

TEST_P(test_constructors, move_constructor) {
    matrix_size_t size = GetParam();
    size_t rows = size.first;
    size_t cols = size.second;

    try {
        MatrixLib::Matrix A(rows, cols);
        MatrixLib::Matrix new_A_move = std::move(A);
        EXPECT_EQ(new_A_move.getRowsSize(), rows)
            << "Error: number of rows does not match when moving";
        EXPECT_EQ(new_A_move.getColsSize(), cols)
            << "Error: number of columns does not match when moving";
        EXPECT_EQ(A.getRowsSize(), 0) << "Error: the moved matrix should be empty";
        EXPECT_EQ(A.getColsSize(), 0) << "Error: the moved matrix should be empty";
    } catch (std::invalid_argument& e) {
        EXPECT_STREQ(e.what(), "Size must be positive");
    } catch (std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "Allocation failed");
    }
}

INSTANTIATE_TEST_SUITE_P(test_constructors_random_sizes, test_constructors,
                         ::testing::ValuesIn(generate_tests_parametrs(100)));
