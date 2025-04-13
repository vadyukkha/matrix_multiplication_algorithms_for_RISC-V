#include "matrix_lib.h"

int main() {
    MatrixLib::Matrix matA(3, 3);
    MatrixLib::Matrix matB(3, 3);

    int value = 1;

    for (size_t i = 0; i < 3; i++) {
        for (size_t j = 0; j < 3; j++) {
            matA.setElement(i, j, value);
            matB.setElement(i, j, value);
            value++;
        }
    }

    std::cout << "Matrix A" << std::endl;
    std::cout << matA << std::endl;

    std::cout << "Matrix B" << std::endl;
    std::cout << matB << std::endl;

    std::cout << "Matrix C = A * B" << std::endl;
    MatrixLib::Matrix matC = matA.multiply(matB);

    std::cout << matC << std::endl;

    return 0;
}
