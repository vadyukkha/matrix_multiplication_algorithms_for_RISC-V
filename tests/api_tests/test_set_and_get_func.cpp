#include <gtest/gtest.h>

#include "matrix_lib.h"
#include "tests_generator.h"

class test_set_and_get : public ::testing::TestWithParam<matrix_size_t> {};

TEST_P(test_set_and_get, set_and_get) {
    auto [rows, cols] = GetParam();

    try {
        MatrixLib::Matrix mat1(rows, cols);

        for (int i = 0; i < mat1.getRowsSize(); i++) {
            for (int j = 0; j < mat1.getColsSize(); j++) {
                mat1.setElement(i, j, 2);
            }
        }

        for (int i = 0; i < mat1.getRowsSize(); i++) {
            for (int j = 0; j < mat1.getColsSize(); j++) {
                EXPECT_EQ(mat1.getElement(i, j), 2) << "Error: element is not equal to 2";
            }
        }
    } catch (std::invalid_argument& e) {
        EXPECT_STREQ(e.what(), "Size must be positive");
    } catch (std::runtime_error& e) {
        EXPECT_STREQ(e.what(), "Allocation failed");
    }
}

INSTANTIATE_TEST_SUITE_P(, test_set_and_get, ::testing::ValuesIn(generate_tests_parametrs(100)));
