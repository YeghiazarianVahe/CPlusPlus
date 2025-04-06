#include "Matrix.h"
#include <stdexcept>

void Matrix::allocate() {
    data = new int*[rows];
    for (int i = 0; i < rows; ++i)
        data[i] = new int[cols];
}

void Matrix::deallocate() {
    for (int i = 0; i < rows; ++i)
        delete[] data[i];
    delete[] data;
}

Matrix::Matrix(int r, int c) : rows(r), cols(c) {
    allocate();
}

Matrix::~Matrix() {
    deallocate();
}

Matrix::Matrix(const Matrix& other) : rows(other.rows), cols(other.cols) {
    allocate();
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            data[i][j] = other.data[i][j];
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        deallocate();
        rows = other.rows;
        cols = other.cols;
        allocate();
        for (int i = 0; i < rows; ++i)
            for (int j = 0; j < cols; ++j)
                data[i][j] = other.data[i][j];
    }
    return *this;
}

void Matrix::input() {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            std::cin >> data[i][j];
}

void Matrix::print() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
            std::cout << data[i][j] << ' ';
        std::cout << '\n';
    }
}

int Matrix::getRows() const { return rows; }
int Matrix::getCols() const { return cols; }
int** Matrix::getData() const { return data; }

Matrix Matrix::add(const Matrix& A, const Matrix& B) {
    if (A.rows != B.rows || A.cols != B.cols)
        throw std::invalid_argument("Add: Matrices must have same dimensions");

    Matrix result(A.rows, A.cols);
    for (int i = 0; i < A.rows; ++i)
        for (int j = 0; j < A.cols; ++j)
            result.data[i][j] = A.data[i][j] + B.data[i][j];
    return result;
}

Matrix Matrix::subtract(const Matrix& A, const Matrix& B) {
    if (A.rows != B.rows || A.cols != B.cols)
        throw std::invalid_argument("Subtract: Matrices must have same dimensions");

    Matrix result(A.rows, A.cols);
    for (int i = 0; i < A.rows; ++i)
        for (int j = 0; j < A.cols; ++j)
            result.data[i][j] = A.data[i][j] - B.data[i][j];
    return result;
}

Matrix Matrix::multiply(const Matrix& A, const Matrix& B) {
    if (A.cols != B.rows)
        throw std::invalid_argument("Multiply: Incompatible dimensions");

    Matrix result(A.rows, B.cols);
    for (int i = 0; i < A.rows; ++i)
        for (int j = 0; j < B.cols; ++j)
            for (int k = 0; k < A.cols; ++k)
                result.data[i][j] += A.data[i][k] * B.data[k][j];
    return result;
}

Matrix Matrix::transpose(const Matrix& A) {
    Matrix result(A.cols, A.rows);
    for (int i = 0; i < A.rows; ++i)
        for (int j = 0; j < A.cols; ++j)
            result.data[j][i] = A.data[i][j];
    return result;
}
