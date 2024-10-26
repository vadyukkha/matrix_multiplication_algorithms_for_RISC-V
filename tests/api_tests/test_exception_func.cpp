#include <gtest/gtest.h>

#include "matrix_lib.h"

TEST(exception, set_element) {
    MatrixLib::Matrix mat1(2, 3);
    try {
        mat1.setElement(10, 12, 1);
        FAIL() << "Exception was not thrown as expected!";
    } catch (const std::out_of_range& e) {
        EXPECT_EQ(std::string(e.what()), "Index out of range");
    }
}

TEST(exception, get_element) {
    MatrixLib::Matrix mat1(2, 3);
    try {
        mat1.getElement(11, 22);
        FAIL() << "Exception was not thrown as expected!";
    } catch (const std::out_of_range& e) {
        EXPECT_EQ(std::string(e.what()), "Index out of range");
    }
}

TEST(exception, multiply) {
    MatrixLib::Matrix mat1(2, 3);
    MatrixLib::Matrix mat2(12, 23);
    try {
        mat1.multiply(mat2);
        FAIL() << "Exception was not thrown as expected!";
    } catch (const std::invalid_argument& e) {
        EXPECT_EQ(std::string(e.what()), "Matrix sizes are not compatible");
    }
}
