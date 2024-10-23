#include "../api/matrix_lib.h"
#include <cassert>

int main() {
    MatrixLib::Matrix mat1(2, 2);

    for (int i = 0; i < mat1.getRows(); i++) {
        for (int j = 0; j < mat1.getCols(); j++) {
            mat1.setElement(i, j, i + j + 1);
        }
    }

    assert(mat1.getElement(0, 0) == 1);
    assert(mat1.getElement(0, 1) == 2);
    assert(mat1.getElement(1, 0) == 2);
    assert(mat1.getElement(1, 1) == 3);

    return 0;
}
