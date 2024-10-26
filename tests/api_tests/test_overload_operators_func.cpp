#include <gtest/gtest.h>

#include "matrix_lib.h"

TEST(overload_operators, copy_operator) {
    MatrixLib::Matrix matrix1(2, 2);
    matrix1.setElement(0, 0, 1);
    matrix1.setElement(0, 1, 2);
    matrix1.setElement(1, 0, 3);
    matrix1.setElement(1, 1, 4);

    MatrixLib::Matrix matrix2;
    matrix2 = matrix1;

    EXPECT_EQ(matrix1.getElement(0, 0), matrix2.getElement(0, 0));
    EXPECT_EQ(matrix1.getElement(0, 1), matrix2.getElement(0, 1));
    EXPECT_EQ(matrix1.getElement(1, 0), matrix2.getElement(1, 0));
    EXPECT_EQ(matrix1.getElement(1, 1), matrix2.getElement(1, 1));
}

TEST(overload_operators, move_operator) {
    MatrixLib::Matrix matrix1(2, 2);
    matrix1.setElement(0, 0, 1);
    matrix1.setElement(0, 1, 2);
    matrix1.setElement(1, 0, 3);
    matrix1.setElement(1, 1, 4);

    MatrixLib::Matrix matrix2;
    matrix2 = std::move(matrix1);

    EXPECT_EQ(0, matrix1.getRows());
    EXPECT_EQ(0, matrix1.getCols());
    EXPECT_EQ(2, matrix2.getRows());
    EXPECT_EQ(2, matrix2.getCols());
    EXPECT_EQ(1, matrix2.getElement(0, 0));
    EXPECT_EQ(2, matrix2.getElement(0, 1));
    EXPECT_EQ(3, matrix2.getElement(1, 0));
    EXPECT_EQ(4, matrix2.getElement(1, 1));
}

TEST(overload_operators, equality_operator) {
    MatrixLib::Matrix matrix1(2, 2);
    matrix1.setElement(0, 0, 1);
    matrix1.setElement(0, 1, 2);
    matrix1.setElement(1, 0, 3);
    matrix1.setElement(1, 1, 4);

    MatrixLib::Matrix matrix2(2, 2);
    matrix2.setElement(0, 0, 1);
    matrix2.setElement(0, 1, 2);
    matrix2.setElement(1, 0, 3);
    matrix2.setElement(1, 1, 4);

    EXPECT_TRUE(matrix1 == matrix2);
}

TEST(overload_operators, inequality_operator) {
    MatrixLib::Matrix matrix1(2, 2);
    matrix1.setElement(0, 0, 1);
    matrix1.setElement(0, 1, 2);
    matrix1.setElement(1, 0, 3);
    matrix1.setElement(1, 1, 4);

    MatrixLib::Matrix matrix2(2, 2);
    matrix2.setElement(0, 0, 1);
    matrix2.setElement(0, 1, 2);
    matrix2.setElement(1, 0, 3);
    matrix2.setElement(1, 1, 5);

    EXPECT_TRUE(matrix1 != matrix2);
}

TEST(overload_operators, multiplication_operator) {
    MatrixLib::Matrix matrix1(2, 2);
    matrix1.setElement(0, 0, 1);
    matrix1.setElement(0, 1, 2);
    matrix1.setElement(1, 0, 3);
    matrix1.setElement(1, 1, 4);

    MatrixLib::Matrix matrix2(2, 2);
    matrix2.setElement(0, 0, 1);
    matrix2.setElement(0, 1, 2);
    matrix2.setElement(1, 0, 3);
    matrix2.setElement(1, 1, 4);

    MatrixLib::Matrix result = matrix1 * matrix2;

    EXPECT_EQ(7, result.getElement(0, 0));
    EXPECT_EQ(10, result.getElement(0, 1));
    EXPECT_EQ(15, result.getElement(1, 0));
    EXPECT_EQ(22, result.getElement(1, 1));
}

TEST(overload_operators, parentheses_operator) {
    MatrixLib::Matrix matrix1(2, 2);
    matrix1.setElement(0, 0, 1);
    matrix1.setElement(0, 1, 2);
    matrix1.setElement(1, 0, 3);
    matrix1.setElement(1, 1, 4);

    EXPECT_EQ(1, matrix1(0, 0));
    EXPECT_EQ(2, matrix1(0, 1));
    EXPECT_EQ(3, matrix1(1, 0));
    EXPECT_EQ(4, matrix1(1, 1));

    matrix1(0, 0) = 5;
    matrix1(0, 1) = 6;
    matrix1(1, 0) = 7;
    matrix1(1, 1) = 8;

    EXPECT_EQ(5, matrix1(0, 0));
    EXPECT_EQ(6, matrix1(0, 1));
    EXPECT_EQ(7, matrix1(1, 0));
    EXPECT_EQ(8, matrix1(1, 1));
}

TEST(overload_operators, output_operator) {
    MatrixLib::Matrix matrix1(2, 2);
    matrix1.setElement(0, 0, 1);
    matrix1.setElement(0, 1, 2);
    matrix1.setElement(1, 0, 3);
    matrix1.setElement(1, 1, 4);

    std::stringstream ss;
    ss << matrix1;

    std::string expected = "1 2 \n3 4 \n";
    EXPECT_EQ(expected, ss.str());
}

TEST(overload_operators, output_operator_empty_matrix) {
    MatrixLib::Matrix matrix1;

    std::stringstream ss;
    ss << matrix1;

    std::string expected = "";
    EXPECT_EQ(expected, ss.str());
}
