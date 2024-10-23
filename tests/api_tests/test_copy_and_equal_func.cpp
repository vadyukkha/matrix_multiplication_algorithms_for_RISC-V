#include "../api/matrix_lib.h"
#include <cassert>

int main() {
    MatrixLib::Matrix mat1(2, 2);

    for (int i = 0; i < mat1.getRows(); i++) {
        for (int j = 0; j < mat1.getCols(); j++) {
            mat1.setElement(i, j, i + j + 1);
        }
    }

    MatrixLib::Matrix mat2 = mat1.copy();

    assert(mat1.isEqual(mat2));

    return 0;
}
