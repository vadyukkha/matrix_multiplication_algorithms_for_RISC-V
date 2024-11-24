#include <gtest/gtest.h>

#include "matrix_lib.h"

TEST(test_set_and_get, set_and_get) {
    size_t rows = 4;
    size_t cols = 6;
    MatrixLib::Matrix mat1(rows, cols);

    for (size_t i = 0; i < mat1.getRowsSize(); i++) {
        for (size_t j = 0; j < mat1.getColsSize(); j++) {
            mat1.setElement(i, j, 2);
        }
    }

    for (size_t i = 0; i < mat1.getRowsSize(); i++) {
        for (size_t j = 0; j < mat1.getColsSize(); j++) {
            EXPECT_EQ(mat1.getElement(i, j), 2) << "Error: element is not equal to 2";
        }
    }
}

TEST(test_set_and_get, set_exception_out_of_range) {
    size_t rows = 4;
    size_t cols = 6;
    MatrixLib::Matrix mat1(rows, cols);

    try {
        mat1.setElement(52, 52, 2);

    } catch (MatrixLib::IndexOutOfRangeMatrix& e) {
        EXPECT_STREQ(e.what(), "Index out of range");
    }
}

TEST(test_set_and_get, get_exception_out_of_range) {
    size_t rows = 4;
    size_t cols = 6;
    MatrixLib::Matrix mat1(rows, cols);

    try {
        mat1.getElement(52, 52);

    } catch (MatrixLib::IndexOutOfRangeMatrix& e) {
        EXPECT_STREQ(e.what(), "Index out of range");
    }
}
