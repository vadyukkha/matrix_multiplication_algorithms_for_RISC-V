#include <gtest/gtest.h>

#include "matrix_lib.h"
#include "tests_generator.h"

class test_setSize : public ::testing::TestWithParam<matrix_size_t> {};

TEST_P(test_setSize, setSize) {
    auto [rows, cols] = GetParam();

    try {
        MatrixLib::Matrix mat(rows, cols);

        mat.setSize(rows - 1, cols - 1);

        EXPECT_EQ(mat.getRowsSize(), rows - 1)
            << "Error: number of rows does not match after changing the size";
        EXPECT_EQ(mat.getColsSize(), cols - 1)
            << "Error: number of columns does not match after changing the size";

        bool alloc_with_zeros = true;
        for (int64_t i = 0; i < rows - 1; ++i) {
            for (int64_t j = 0; j < cols - 1; ++j) {
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

INSTANTIATE_TEST_SUITE_P(test_setSize_random_sizes, test_setSize,
                         ::testing::ValuesIn(generate_tests_parametrs(100)));
