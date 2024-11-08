#include <gtest/gtest.h>

#include "matrix_lib.h"
#include "tests_generator.h"

class test_setSize : public ::testing::TestWithParam<matrix_size_t> {};

TEST_P(test_setSize, setSize1) {
    matrix_size_t size = GetParam();
    size_t rows = size.first;
    size_t cols = size.second;

    try {
        MatrixLib::Matrix mat(rows, cols);

        mat.setSize(rows * 2, cols * 2);

        EXPECT_EQ(mat.getRowsSize(), rows * 2)
            << "Error: number of rows does not match after changing the size";
        EXPECT_EQ(mat.getColsSize(), cols * 2)
            << "Error: number of columns does not match after changing the size";

        bool alloc_with_zeros = true;
        for (size_t i = 0; i < rows * 2; ++i) {
            for (size_t j = 0; j < cols * 2; ++j) {
                EXPECT_EQ(mat.getElement(i, j), 0)
                    << "Error: element is not zero after changing the size";
                if (mat.getElement(i, j) != 0) {
                    alloc_with_zeros = false;
                    break;
                }
            }
            if (!alloc_with_zeros) {
                break;
            }
        }
    } catch (std::invalid_argument& e) {
        // EXPECT_STREQ(e.what(), "Size must be positive");
        EXPECT_TRUE(strcmp(e.what(), "Size must be positive") == 0 ||
                    strcmp(e.what(), "Rows and cols must be positive") == 0);
        // EXPECT_STREQ(e.what(), "Rows and cols must be positive");
    } catch (std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "Allocation failed");
    }
}

TEST(test_setSize, setSize_constriction) {
    size_t rows = 4;
    size_t cols = 4;

    MatrixLib::Matrix mat(rows, cols);

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            mat.setElement(i, j, i * cols + j + 1);
        }
    }

    size_t new_rows = 3;
    size_t new_cols = 3;

    mat.setSize(new_rows, new_cols);

    for (size_t i = 0; i < new_rows; ++i) {
        for (size_t j = 0; j < new_cols; ++j) {
            if (i < rows && j < cols) {
                EXPECT_EQ(mat.getElement(i, j), i * cols + j + 1)
                    << "Error: element is not equal after changing the size";
            } else {
                EXPECT_EQ(mat.getElement(i, j), 0)
                    << "Error: element is not zero after changing the size";
            }
        }
    }
}

TEST(test_setSize, setSize_extension) {
    size_t rows = 3;
    size_t cols = 3;

    MatrixLib::Matrix mat(rows, cols);

    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            mat.setElement(i, j, i * cols + j + 1);
        }
    }

    std::cout << mat << std::endl;
    size_t new_rows = 4;
    size_t new_cols = 4;

    mat.setSize(new_rows, new_cols);

    std::cout << mat << std::endl;

    for (size_t i = 0; i < new_rows; ++i) {
        for (size_t j = 0; j < new_cols; ++j) {
            if (i < rows && j < cols) {
                EXPECT_EQ(mat.getElement(i, j), i * cols + j + 1)
                    << "Error: element is not equal after changing the size";
            } else {
                EXPECT_EQ(mat.getElement(i, j), 0)
                    << "Error: element is not zero after changing the size";
            }
        }
    }
}

INSTANTIATE_TEST_SUITE_P(test_setSize_random_sizes, test_setSize,
                         ::testing::ValuesIn(generate_tests_parametrs(100)));
