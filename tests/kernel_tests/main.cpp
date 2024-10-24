#include <gtest/gtest.h>

#include "matrix_lib.h"

int main(int argc, char **argv) {
    MatrixLib::Matrix A;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
