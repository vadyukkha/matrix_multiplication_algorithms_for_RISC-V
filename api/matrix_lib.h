#ifndef API_MATRIXLIB_H
#define API_MATRIXLIB_H

#include <iostream>
#include <stdexcept>

// Include C header file
extern "C" {
#include "matrix_operation.h"
}

namespace MatrixLib {

class Matrix {
   public:
    // Constructor
    explicit Matrix(const size_t rows, const size_t cols) noexcept;

    // Defualt constructor
    explicit Matrix() noexcept;

    // Copy constructor
    Matrix(const Matrix& other);

    // Move constructor
    Matrix(Matrix&& other) noexcept;

    // Getting size rows
    size_t getRows() const noexcept;

    // Getting size cols
    size_t getCols() const noexcept;

    // Setting size
    void setSize(const size_t rows, const size_t cols);

    // Setting element
    void setElement(size_t row, size_t col, int value);

    // Getting element
    int getElement(size_t row, size_t col) const;

    // Multyply two matrix
    Matrix multiply(const Matrix& other) const;

    // Equality two matrix
    bool isEqual(const Matrix& other) const noexcept;

    // Print matrix
    void print() const noexcept;

    // Copy matrix
    Matrix copy() const;

    // Destructor
    ~Matrix() noexcept;

   private:
    size_t rows_;
    size_t cols_;
    int* data_;
};

}  // namespace MatrixLib

#endif  // MATRIXLIB_H
