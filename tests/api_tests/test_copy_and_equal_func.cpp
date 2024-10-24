#include <gtest/gtest.h>

#include "matrix_lib.h"

TEST(copy_and_equal, test_copy_and_equal_func) {
    MatrixLib::Matrix mat1(2, 2);

    for (int i = 0; i < mat1.getRows(); i++) {
        for (int j = 0; j < mat1.getCols(); j++) {
            mat1.setElement(i, j, i + j + 1);
        }
    }

    MatrixLib::Matrix mat2 = mat1.copy();

    EXPECT_EQ(mat1.isEqual(mat2), true);
}
