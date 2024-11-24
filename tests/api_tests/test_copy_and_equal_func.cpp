#include <gtest/gtest.h>

#include "matrix_lib.h"

TEST(test_copy_and_equal, copy_and_equal) {
    size_t rows = 6;
    size_t cols = 2;

    MatrixLib::Matrix mat1(rows, cols);

    for (size_t i = 0; i < mat1.getRowsSize(); i++) {
        for (size_t j = 0; j < mat1.getColsSize(); j++) {
            mat1.setElement(i, j, 3);
        }
    }
    
    MatrixLib::Matrix mat2 = mat1.copy();
    EXPECT_EQ(mat1.isEqual(mat2), true);
}
