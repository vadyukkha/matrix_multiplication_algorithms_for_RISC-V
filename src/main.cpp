#include "../api/MatrixLib.h"

int main() {
    // Создание двух матриц 2x2
    MatrixLib::Matrix mat1(2, 2);
    MatrixLib::Matrix mat2(2, 2);

    // Заполняем первую матрицу
    mat1.setElement(0, 0, 1);
    mat1.setElement(0, 1, 2);
    mat1.setElement(1, 0, 3);
    mat1.setElement(1, 1, 4);

    // Заполняем вторую матрицу
    mat2.setElement(0, 0, 5);
    mat2.setElement(0, 1, 6);
    mat2.setElement(1, 0, 7);
    mat2.setElement(1, 1, 8);

    std::cout << "Матрица 1:" << std::endl;
    mat1.print();

    std::cout << "Матрица 2:" << std::endl;
    mat2.print();

    // Умножение матриц
    MatrixLib::Matrix product = mat1.multiply(mat2);
    std::cout << "Произведение матриц:" << std::endl;
    product.print();

    return 0;
}
