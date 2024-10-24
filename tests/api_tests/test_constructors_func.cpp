#include <gtest/gtest.h>

#include "matrix_lib.h"

TEST(constructors, test_constructors_func) {
    MatrixLib::Matrix mat1(2, 3);
    EXPECT_EQ(mat1.getRows(), 2);
    EXPECT_EQ(mat1.getCols(), 3);

    MatrixLib::Matrix mat2;
    EXPECT_EQ(mat2.getRows(), 0);
    EXPECT_EQ(mat2.getCols(), 0);

    MatrixLib::Matrix mat3 = mat1;
    EXPECT_EQ(mat3.getRows(), 2);
    EXPECT_EQ(mat3.getCols(), 3);

    MatrixLib::Matrix mat4 = std::move(mat1);
    EXPECT_EQ(mat4.getRows(), 2);
    EXPECT_EQ(mat4.getCols(), 3);
    EXPECT_EQ(mat1.getRows(), 0);
    EXPECT_EQ(mat1.getCols(), 0);
}
