#ifndef API_MATRIXLIB_H
#define API_MATRIXLIB_H

#include <iostream>
#include <stdexcept>

namespace MatrixLib {

class Matrix {
   public:
    // Constructor
    explicit Matrix(const size_t rows, const size_t cols);

    // Defualt constructor
    explicit Matrix() noexcept;

    // Copy constructor
    Matrix(const Matrix& other);

    // Move constructor
    Matrix(Matrix&& other) noexcept;

    // Getting size rows
    size_t getRowsSize() const noexcept;

    // Getting size cols
    size_t getColsSize() const noexcept;

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

    // Copy matrix
    Matrix copy() const;

    // Destructor
    ~Matrix() noexcept;

    // Overload copy operator =
    Matrix& operator=(const Matrix& other);

    // Overload move operator =
    Matrix& operator=(Matrix&& other) noexcept;

    // Overload operator ==
    bool operator==(const Matrix& other) const noexcept;

    // Overload operator !=
    bool operator!=(const Matrix& other) const noexcept;

    // Overload operator *
    Matrix operator*(const Matrix& other) const;

    // Overload operator ()
    int& operator()(size_t row, size_t col);

    // Overload operator <<
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

   private:
    size_t rows_;
    size_t cols_;
    int* data_;
};

class MatrixException : public std::exception {
   public:
    explicit MatrixException(const char* message) : message_(message) {}

    const char* what() const noexcept override { return message_; }

   private:
    const char* message_;
};

class InvalidMatrixSize : public MatrixException {
   public:
    explicit InvalidMatrixSize(const char* message) : MatrixException(message) {}
};

class IncompatibleMatrixSizes : public MatrixException {
   public:
    explicit IncompatibleMatrixSizes(const char* message) : MatrixException(message) {}
};

class IndexOutOfRangeMatrix : public MatrixException {
   public:
    explicit IndexOutOfRangeMatrix(const char* message) : MatrixException(message) {}
};

class AllocationError : public MatrixException {
   public:
    explicit AllocationError(const char* message) : MatrixException(message) {}
};

class NoInitializedMatrix : public MatrixException {
   public:
    explicit NoInitializedMatrix(const char* message) : MatrixException(message) {}
};

}  // namespace MatrixLib

#endif  // MATRIXLIB_H
