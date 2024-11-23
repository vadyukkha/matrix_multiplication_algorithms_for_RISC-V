#include <gtest/gtest.h>
#include <numeric>

#include "matrix_lib.h"

TEST(test_constructors, default_constructor) {
    MatrixLib::Matrix mat;
    EXPECT_EQ(mat.getRowsSize(), 0)
        << "Error: number of rows in the default constructor is not equal to 0";
    EXPECT_EQ(mat.getColsSize(), 0)
        << "Error: number of columns in the default constructor is not equal to 0";
}

TEST(test_constructors, main_constructor) {
    size_t rows = 2;
    size_t cols = 3;
    
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
}

TEST(test_constructors, main_constructor_exception_alloc) {
    size_t rows = std::numeric_limits<int>::max();
    size_t cols = std::numeric_limits<int>::max();

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
    } catch (MatrixLib::AllocationError& e) {
        EXPECT_STREQ(e.what(), "Allocation failed");
    }
}

TEST(test_constructors, copy_constructor) {
    size_t rows = 4;
    size_t cols = 3;

    MatrixLib::Matrix A(rows, cols);
    MatrixLib::Matrix new_A_copy = A;

    EXPECT_EQ(new_A_copy.getRowsSize(), rows)
        << "Error: number of rows does not match when copying";
    EXPECT_EQ(new_A_copy.getColsSize(), cols)
        << "Error: number of columns does not match when copying";
}

TEST(test_constructors, copy_constructor_exception_alloc) {
    size_t rows = std::numeric_limits<int>::max();
    size_t cols = std::numeric_limits<int>::max();

    try {
        MatrixLib::Matrix A(rows, cols);
        MatrixLib::Matrix new_A_copy = A;

        EXPECT_EQ(new_A_copy.getRowsSize(), rows)
            << "Error: number of rows does not match when copying";
        EXPECT_EQ(new_A_copy.getColsSize(), cols)
            << "Error: number of columns does not match when copying";
    } catch (MatrixLib::AllocationError& e) {
        EXPECT_STREQ(e.what(), "Allocation failed");
    }
}

TEST(test_constructors, move_constructor) {
    size_t rows = 5;
    size_t cols = 6;

    MatrixLib::Matrix A(rows, cols);
    MatrixLib::Matrix new_A_move = std::move(A);

    EXPECT_EQ(new_A_move.getRowsSize(), rows)
        << "Error: number of rows does not match when moving";
    EXPECT_EQ(new_A_move.getColsSize(), cols)
        << "Error: number of columns does not match when moving";
    EXPECT_EQ(A.getRowsSize(), 0) << "Error: the moved matrix should be empty";
    EXPECT_EQ(A.getColsSize(), 0) << "Error: the moved matrix should be empty";
}

TEST(test_constructors, move_constructor_exception_alloc) {
    size_t rows = std::numeric_limits<int>::max();
    size_t cols = std::numeric_limits<int>::max();

    try {
        MatrixLib::Matrix A(rows, cols);
        MatrixLib::Matrix new_A_move = std::move(A);

        EXPECT_EQ(new_A_move.getRowsSize(), rows)
            << "Error: number of rows does not match when moving";
        EXPECT_EQ(new_A_move.getColsSize(), cols)
            << "Error: number of columns does not match when moving";
        EXPECT_EQ(A.getRowsSize(), 0) << "Error: the moved matrix should be empty";
        EXPECT_EQ(A.getColsSize(), 0) << "Error: the moved matrix should be empty";
    } catch (MatrixLib::AllocationError& e) {
        EXPECT_STREQ(e.what(), "Allocation failed");
    }
}