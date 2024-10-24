#include "matrix_lib.h"

namespace MatrixLib {

Matrix::Matrix(const size_t rows, const size_t cols) : rows_(rows), cols_(cols) {
    data_ = new int[rows * cols];
}

Matrix::Matrix() : rows_(0), cols_(0) { data_ = nullptr; }

Matrix::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
    data_ = new int[rows_ * cols_];
    for (int i = 0; i < rows_ * cols_; ++i) {
        data_[i] = other.data_[i];
    }
}

Matrix::Matrix(Matrix&& other) : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {
    other.rows_ = 0;
    other.cols_ = 0;
    other.data_ = nullptr;
}

Matrix::~Matrix() { delete[] data_; }

size_t Matrix::getRows() const { return rows_; }

size_t Matrix::getCols() const { return cols_; }

void Matrix::setSize(const size_t rows, const size_t cols) {
    rows_ = rows;
    cols_ = cols;
}

void Matrix::setElement(size_t row, size_t col, int value) {
    if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
        throw std::out_of_range("Index out of range");
    }
    data_[row * cols_ + col] = value;
}

int Matrix::getElement(size_t row, size_t col) const {
    if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
        throw std::out_of_range("Index out of range");
    }
    return data_[row * cols_ + col];
}

Matrix Matrix::multiply(const Matrix& other) const {
    if (cols_ != other.rows_) {
        throw std::invalid_argument("Matrix sizes are not compatible");
    }

    Matrix result(rows_, other.cols_);
    matmul_naive(this->data_, other.data_, result.data_, rows_, other.cols_);
    return result;
}

void Matrix::print() const {
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            std::cout << data_[i * cols_ + j] << " ";
        }
        std::cout << std::endl;
    }
}

bool Matrix::isEqual(const Matrix& other) const {
    if (rows_ != other.rows_ || cols_ != other.cols_) {
        return false;
    }

    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            if (data_[i * cols_ + j] != other.data_[i * cols_ + j]) {
                return false;
            }
        }
    }

    return true;
}

Matrix Matrix::copy() const {
    Matrix result(rows_, cols_);
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            result.data_[i * cols_ + j] = data_[i * cols_ + j];
        }
    }
    return result;
}

}  // namespace MatrixLib
