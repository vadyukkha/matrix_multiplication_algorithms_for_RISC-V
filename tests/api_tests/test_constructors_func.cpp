#include <gtest/gtest.h>

#include "matrix_lib.h"

TEST(constructors, main_constructor) {
    MatrixLib::Matrix mat1(2, 3);
    EXPECT_EQ(mat1.getRows(), 2);
    EXPECT_EQ(mat1.getCols(), 3);
}

TEST(constructors, default_constructor) {
    MatrixLib::Matrix mat2;
    EXPECT_EQ(mat2.getRows(), 0);
    EXPECT_EQ(mat2.getCols(), 0);
}

TEST(constructors, copy_constructor) {
    MatrixLib::Matrix mat1(2, 3);

    MatrixLib::Matrix mat3 = mat1;
    EXPECT_EQ(mat3.getRows(), 2);
    EXPECT_EQ(mat3.getCols(), 3);
}

TEST(constructors, move_constructor) {
    MatrixLib::Matrix mat1(2, 3);

    MatrixLib::Matrix mat4 = std::move(mat1);
    EXPECT_EQ(mat4.getRows(), 2);
    EXPECT_EQ(mat4.getCols(), 3);
    EXPECT_EQ(mat1.getRows(), 0);
    EXPECT_EQ(mat1.getCols(), 0);
}

TEST(constructors, negative_size) {
    try {
        MatrixLib::Matrix mat5(-3, -4);
        FAIL() << "Expected std::invalid_argument";
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ(e.what(), "Size must be positive");
    }
}
