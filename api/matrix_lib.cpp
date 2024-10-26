#include "matrix_lib.h"

#include <algorithm>
#include <iostream>

namespace MatrixLib {

Matrix::Matrix(const int64_t rows, const int64_t cols) {
    if (rows < 0 || cols < 0) {
        throw std::invalid_argument("Size must be positive");
    }
    rows_ = rows;
    cols_ = cols;

    try {
        data_ = new int[rows_ * cols_]();
    } catch (std::bad_alloc& e) {
        throw std::runtime_error("Allocation failed");
    }
}

Matrix::Matrix() noexcept : rows_(0), cols_(0) { data_ = nullptr; }

Matrix::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
    try {
        data_ = new int[rows_ * cols_]();
    } catch (std::bad_alloc& e) {
        throw std::runtime_error("Allocation failed");
    }

    std::copy(other.data_, other.data_ + rows_ * cols_, data_);
}

Matrix::Matrix(Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), data_(other.data_) {
    other.data_ = nullptr;
    other.rows_ = 0;
    other.cols_ = 0;
}

Matrix::~Matrix() noexcept { delete[] data_; }

size_t Matrix::getRows() const noexcept { return rows_; }

size_t Matrix::getCols() const noexcept { return cols_; }

void Matrix::setSize(const int64_t rows, const int64_t cols) {
    if (rows < 0 || cols < 0) {
        throw std::invalid_argument("Rows and cols must be positive");
    }
    int* old_data = data_;

    try {
        data_ = new int[rows * cols]();
    } catch (std::bad_alloc& e) {
        throw std::runtime_error("Allocation failed");
    }

    for (size_t i = 0; i < rows && i < rows_; ++i) {
        for (size_t j = 0; j < cols && j < cols_; ++j) {
            data_[i * cols + j] = old_data[i * cols_ + j];
        }
    }
    rows_ = rows;
    cols_ = cols;
    delete[] old_data;
}

void Matrix::setElement(int64_t row, int64_t col, int value) {
    if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
        throw std::out_of_range("Index out of range");
    }
    data_[row * cols_ + col] = value;
}

int Matrix::getElement(int64_t row, int64_t col) const {
    if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
        throw std::out_of_range("Index out of range");
    }
    return data_[row * cols_ + col];
}

Matrix Matrix::multiply(const Matrix& other) const {
    if (cols_ != other.rows_) {
        throw std::invalid_argument("Matrix sizes are not compatible");
    }

    if (other.data_ == nullptr || data_ == nullptr) {
        throw std::invalid_argument("No initialized matrix");
    }

    Matrix result(rows_, other.cols_);
    matmul_naive(this->data_, other.data_, result.data_, rows_, other.cols_);
    return result;
}

void Matrix::print() const noexcept {
    for (size_t i = 0; i < rows_; ++i) {
        for (size_t j = 0; j < cols_; ++j) {
            std::cout << data_[i * cols_ + j] << " ";
        }
        std::cout << std::endl;
    }
}

bool Matrix::isEqual(const Matrix& other) const noexcept {
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
    std::copy(data_, data_ + rows_ * cols_, result.data_);
    return result;
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) {
        return *this;
    }

    if (data_ != nullptr) {
        delete[] data_;
    }

    rows_ = other.rows_;
    cols_ = other.cols_;
    try {
        data_ = new int[rows_ * cols_]();
    } catch (std::bad_alloc& e) {
        throw std::runtime_error("Allocation failed");
    }

    std::copy(other.data_, other.data_ + rows_ * cols_, data_);
    return *this;
}

Matrix& Matrix::operator=(Matrix&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    if (data_ != nullptr) {
        delete[] data_;
    }

    rows_ = other.rows_;
    cols_ = other.cols_;
    data_ = std::move(other.data_);
    other.data_ = nullptr;
    other.rows_ = 0;
    other.cols_ = 0;
    return *this;
}

bool Matrix::operator==(const Matrix& other) const noexcept { return isEqual(other); }

bool Matrix::operator!=(const Matrix& other) const noexcept { return !isEqual(other); }

Matrix Matrix::operator*(const Matrix& other) const { return multiply(other); }

int& Matrix::operator()(int64_t row, int64_t col) {
    if (row >= rows_ || col >= cols_ || row < 0 || col < 0) {
        throw std::out_of_range("Index out of range");
    }
    return data_[row * cols_ + col];
}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (size_t i = 0; i < matrix.rows_; ++i) {
        for (size_t j = 0; j < matrix.cols_; ++j) {
            os << matrix.data_[i * matrix.cols_ + j] << " ";
        }
        os << std::endl;
    }
    return os;
}

}  // namespace MatrixLib
