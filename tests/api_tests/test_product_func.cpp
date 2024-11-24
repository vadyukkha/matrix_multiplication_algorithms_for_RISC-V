#include <gtest/gtest.h>

#include "matrix_lib.h"

TEST(product, test_product_func) {
    MatrixLib::Matrix mat1(2, 2);
    MatrixLib::Matrix mat2(2, 2);

    for (size_t i = 0; i < mat1.getRowsSize(); i++) {
        for (size_t j = 0; j < mat1.getColsSize(); j++) {
            mat1.setElement(i, j, i + j + 1);
        }
    }

    for (size_t i = 0; i < mat2.getRowsSize(); i++) {
        for (size_t j = 0; j < mat2.getColsSize(); j++) {
            mat2.setElement(i, j, i + j + 5);
        }
    }

    MatrixLib::Matrix product = mat1.multiply(mat2);

    EXPECT_EQ(product.getElement(0, 0), 1 * 5 + 2 * 6);
    EXPECT_EQ(product.getElement(0, 1), 1 * 6 + 2 * 7);
    EXPECT_EQ(product.getElement(1, 0), 2 * 5 + 3 * 6);
    EXPECT_EQ(product.getElement(1, 1), 2 * 6 + 3 * 7);
}

TEST(product, test_product_func_no_init) {
    MatrixLib::Matrix mat1;
    MatrixLib::Matrix mat2;
    try {
        MatrixLib::Matrix product = mat1.multiply(mat2);
    } catch (MatrixLib::NoInitializedMatrix &e) {
        EXPECT_STREQ(e.what(), "No initialized matrix");
    }
}

TEST(product, test_product_func_incompatible) {
    MatrixLib::Matrix mat1(3, 3);
    MatrixLib::Matrix mat2(2, 2);
    try {
        MatrixLib::Matrix product = mat1.multiply(mat2);
    } catch (MatrixLib::IncompatibleMatrixSizes &e) {
        EXPECT_STREQ(e.what(), "Matrix sizes are not compatible");
    }
}
