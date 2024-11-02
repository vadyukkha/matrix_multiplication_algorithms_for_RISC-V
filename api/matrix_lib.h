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

    // Print matrix
    void print() const noexcept;

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

}  // namespace MatrixLib

#endif  // MATRIXLIB_H
