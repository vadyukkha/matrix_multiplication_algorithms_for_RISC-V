#ifndef API_MATRIXLIB_H
#define API_MATRIXLIB_H

#include <iostream>
#include <stdexcept>

// Include C header file
extern "C" {
    #include "../include/matrix_operation.h"
}

namespace MatrixLib {

    class Matrix {
    public:
        // Constructor
        Matrix(const size_t rows, const size_t cols);

        //Defualt constructor
        Matrix();

        // Copy constructor
        Matrix(const Matrix& other);

        // Move constructor
        Matrix(Matrix&& other);

        // Getting size rows
        size_t getRows() const;

        // Getting size cols
        size_t getCols() const;

        // Setting size
        void setSize(const size_t rows, const size_t cols);

        // Setting element
        void setElement(size_t row, size_t col, int value);

        // Getting element
        int getElement(size_t row, size_t col) const;

        // Multyply two matrix
        Matrix multiply(const Matrix& other) const;

        // Equality two matrix
        bool isEqual(const Matrix& other) const;

        // Print matrix
        void print() const;

        // Copy matrix
        Matrix copy() const;

        // Destructor
        ~Matrix();

    private:
        size_t rows_;
        size_t cols_;
        int *data_;
    };

} // namespace MatrixLib

#endif // MATRIXLIB_H
