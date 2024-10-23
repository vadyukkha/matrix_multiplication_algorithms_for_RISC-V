#include "../api/matrix_lib.h"
#include <cassert>

int main() {
    MatrixLib::Matrix mat1(2, 3);
    assert(mat1.getRows() == 2);
    assert(mat1.getCols() == 3);

    MatrixLib::Matrix mat2;
    assert(mat2.getRows() == 0);
    assert(mat2.getCols() == 0);

    MatrixLib::Matrix mat3 = mat1;
    assert(mat3.getRows() == 2);
    assert(mat3.getCols() == 3);

    MatrixLib::Matrix mat4 = std::move(mat1);
    assert(mat4.getRows() == 2);
    assert(mat4.getCols() == 3);
    assert(mat1.getRows() == 0);
    assert(mat1.getCols() == 0);

    return 0;
}
