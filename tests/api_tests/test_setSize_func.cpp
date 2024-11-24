#include <gtest/gtest.h>

#include "matrix_lib.h"

TEST(test_setSize, setSize) {
    size_t rows = 8;
    size_t cols = 5;
    MatrixLib::Matrix mat(rows, cols);

    mat.setSize(rows * 2, cols * 2);

    EXPECT_EQ(mat.getRowsSize(), rows * 2)
        << "Error: number of rows does not match after changing the size";
    EXPECT_EQ(mat.getColsSize(), cols * 2)
        << "Error: number of columns does not match after changing the size";

    bool alloc_with_zeros = true;
    for (size_t i = 0; i < rows * 2; ++i) {
        for (size_t j = 0; j < cols * 2; ++j) {
            EXPECT_EQ(mat.getElement(i, j), 0)
                << "Error: element is not zero after changing the size";
            if (mat.getElement(i, j) != 0) {
                alloc_with_zeros = false;
                break;
            }
        }
        if (!alloc_with_zeros) {
            break;
        }
    }
}

TEST(test_setSize, setSize_exception_invalid_size) {
    size_t rows = 8;
    size_t cols = 5;
    MatrixLib::Matrix mat(rows, cols);
    try {
        mat.setSize(0, 0);
    } catch (MatrixLib::InvalidMatrixSize& e) {
        EXPECT_STREQ(e.what(), "Rows and cols must be positive");
    }
}

TEST(test_setSize, setSize_exception_alloc) {
    size_t rows = 8;
    size_t cols = 5;
    MatrixLib::Matrix mat(rows, cols);
    try {
        mat.setSize(std::numeric_limits<int>::max(), std::numeric_limits<int>::max());
    } catch (MatrixLib::AllocationError& e) {
        EXPECT_STREQ(e.what(), "Allocation failed");
    }
}
