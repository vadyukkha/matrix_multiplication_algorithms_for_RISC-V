#include <gtest/gtest.h>

#include "matrix_lib.h"

TEST(set_and_get, test_set_and_get_func) {
    MatrixLib::Matrix mat1(2, 2);

    for (int i = 0; i < mat1.getRows(); i++) {
        for (int j = 0; j < mat1.getCols(); j++) {
            mat1.setElement(i, j, i + j + 1);
        }
    }

    EXPECT_EQ(mat1.getElement(0, 0), 1);
    EXPECT_EQ(mat1.getElement(0, 1), 2);
    EXPECT_EQ(mat1.getElement(1, 0), 2);
    EXPECT_EQ(mat1.getElement(1, 1), 3);
}
