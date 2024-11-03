#include "matrix_lib.h"

#include <algorithm>
#include <iostream>

// Include C header file
extern "C" {
#include "matrix_operation.h"
}

namespace MatrixLib {

Matrix::Matrix(const size_t rows, const size_t cols) {
    if (rows == 0 || cols == 0) {
        throw MatrixLib::InvalidSize("Size must be positive");
    }
    rows_ = rows;
    cols_ = cols;

    try {
        data_ = new int[rows_ * cols_]();
    } catch (std::bad_alloc& e) {
        throw MatrixLib::AllocationError("Allocation failed");
    }
}

Matrix::Matrix() noexcept : rows_(0), cols_(0) { data_ = nullptr; }

Matrix::Matrix(const Matrix& other) : rows_(other.rows_), cols_(other.cols_) {
    try {
        data_ = new int[rows_ * cols_]();
    } catch (std::bad_alloc& e) {
        throw MatrixLib::AllocationError("Allocation failed");
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

size_t Matrix::getRowsSize() const noexcept { return rows_; }

size_t Matrix::getColsSize() const noexcept { return cols_; }

void Matrix::setSize(const size_t rows, const size_t cols) {
    if (rows == 0 || cols == 0) {
        throw MatrixLib::InvalidSize("Rows and cols must be positive");
    }
    int* old_data = data_;

    try {
        data_ = new int[rows * cols]();
    } catch (std::bad_alloc& e) {
        throw MatrixLib::AllocationError("Allocation failed");
    }

    for (size_t i = 0; i < std::min(rows, rows_); ++i) {
        std::copy_n(old_data + i * cols_, std::min(cols, cols_), data_ + i * cols);
    }

    rows_ = rows;
    cols_ = cols;
    delete[] old_data;
}

void Matrix::setElement(size_t row, size_t col, int value) {
    if (row >= rows_ || col >= cols_) {
        throw MatrixLib::IndexOutOfRange("Index out of range");
    }
    data_[row * cols_ + col] = value;
}

int Matrix::getElement(size_t row, size_t col) const {
    if (row >= rows_ || col >= cols_) {
        throw MatrixLib::IndexOutOfRange("Index out of range");
    }
    return data_[row * cols_ + col];
}

Matrix Matrix::multiply(const Matrix& other) const {
    if (cols_ != other.rows_) {
        throw MatrixLib::IncompatibleMatrixSizes("Matrix sizes are not compatible");
    }

    if (other.data_ == nullptr || data_ == nullptr) {
        throw MatrixLib::NoInitializedMatrix("No initialized matrix");
    }

    Matrix result(rows_, other.cols_);
    matmul_naive(this->data_, other.data_, result.data_, rows_, cols_, other.cols_);
    return result;
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
        throw MatrixLib::AllocationError("Allocation failed");
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

int& Matrix::operator()(size_t row, size_t col) {
    if (row >= rows_ || col >= cols_) {
        throw MatrixLib::IndexOutOfRange("Index out of range");
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
