#include "../api/matrix_lib.h"
#include <cassert>

int main() {
    MatrixLib::Matrix mat1(2, 2);
    MatrixLib::Matrix mat2(2, 2);

    for (int i = 0; i < mat1.getRows(); i++) {
        for (int j = 0; j < mat1.getCols(); j++) {
            mat1.setElement(i, j, i + j + 1);
        }
    }

    for (int i = 0; i < mat2.getRows(); i++) {
        for (int j = 0; j < mat2.getCols(); j++) {
            mat2.setElement(i, j, i + j + 5);
        }
    }

    MatrixLib::Matrix product = mat1.multiply(mat2);

    assert(product.getElement(0, 0) == 1 * 5 + 2 * 6);
    assert(product.getElement(0, 1) == 1 * 6 + 2 * 7);
    assert(product.getElement(1, 0) == 2 * 5 + 3 * 6);
    assert(product.getElement(1, 1) == 2 * 6 + 3 * 7);

    return 0;
}
