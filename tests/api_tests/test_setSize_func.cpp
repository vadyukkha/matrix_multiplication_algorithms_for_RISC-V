#include <gtest/gtest.h>

#include "matrix_lib.h"

TEST(setSize, test_setSize_func) {
    MatrixLib::Matrix A(5, 5);
    A.setElement(4, 4, 9);
    EXPECT_EQ(A.getElement(4, 4), 9);

    A.setSize(10, 10);

    EXPECT_EQ(A.getElement(4, 4), 9);

    A.setSize(2, 2);
    try {
        A.getElement(4, 4);
        FAIL() << "Exception was not thrown as expected!";
    } catch (const std::out_of_range& e) {
        EXPECT_EQ(std::string(e.what()), "Index out of range");
    }
}