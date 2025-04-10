#include "matrix_toolbox.h"
#include <iostream>
#include <stdexcept>

Matrix::Matrix(size_t row, size_t col) : rows{row}, cols{col} {
    if (row <= 0 || col <= 0)
        throw std::invalid_argument("Rows and columns must be positive integers.");

    data = new double*[rows];
    for (size_t i = 0; i < rows; ++i)
        data[i] = new double[cols] {};
}

Matrix::~Matrix() {
    for (size_t i = 0; i < cols; ++i)
        delete[] data[i];
    delete[] data;    
}

void Matrix::print() const {
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            std::cout << data[i][j] << ' ';
        }
        std::cout << ' \n ';
    }
}

Matrix Matrix::add(const Matrix& B) const {
    if (rows != B.rows || cols != B.cols)
        throw std::invalid_argument("Matrix sizes must match for addition");

    Matrix result(rows, cols);
    for (size_t i = 0; i < rows; ++i){
        for (size_t j = 0; j < cols; ++j){
            result.data[i][j] = this->data[i][j] + B.data[i][j];
        }    
    }
    return result;
}

Matrix Matrix::multiply(const Matrix& B) const {
    if (cols != B.rows)
        throw std::invalid_argument("Incompatible dimensions. A matrix cols must be equal to B matrix rows.");

    Matrix result(rows, B.cols);
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < B.cols; ++j)
            for (int k = 0; k < cols; ++k)
                result.data[i][j] += this->data[i][k] * B.data[k][j];
    return result;
}