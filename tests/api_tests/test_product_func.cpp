#include <gtest/gtest.h>

#include "matrix_lib.h"

TEST(product, test_product_func) {
    MatrixLib::Matrix mat1(2, 2);
    MatrixLib::Matrix mat2(2, 2);

    for (int i = 0; i < mat1.getRowsSize(); i++) {
        for (int j = 0; j < mat1.getColsSize(); j++) {
            mat1.setElement(i, j, i + j + 1);
        }
    }

    for (int i = 0; i < mat2.getRowsSize(); i++) {
        for (int j = 0; j < mat2.getColsSize(); j++) {
            mat2.setElement(i, j, i + j + 5);
        }
    }

    MatrixLib::Matrix product = mat1.multiply(mat2);

    EXPECT_EQ(product.getElement(0, 0), 1 * 5 + 2 * 6);
    EXPECT_EQ(product.getElement(0, 1), 1 * 6 + 2 * 7);
    EXPECT_EQ(product.getElement(1, 0), 2 * 5 + 3 * 6);
    EXPECT_EQ(product.getElement(1, 1), 2 * 6 + 3 * 7);

    MatrixLib::Matrix mat3;
    MatrixLib::Matrix mat4;

    try {
        MatrixLib::Matrix Error_matrix = mat3.multiply(mat4);
        FAIL() << "Exception was not thrown as expected!";
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ(e.what(), "No initialized matrix");
    }
}
