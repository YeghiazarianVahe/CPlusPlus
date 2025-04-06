#ifndef MATRIX_CALC_H
#define MATRIX_CALC_H



#include <iostream>

class Matrix {
private:
    int** data;
    int rows, cols;

    void allocate();
    void deallocate();

public:
    Matrix(int rows, int cols);
    Matrix(const Matrix& other);              // Copy constructor
    Matrix& operator=(const Matrix& other);   // Copy assignment
    ~Matrix();

    void input();
    void print() const;

    int getRows() const;
    int getCols() const;
    int** getData() const;

    static Matrix add(const Matrix& A, const Matrix& B);
    static Matrix subtract(const Matrix& A, const Matrix& B);
    static Matrix multiply(const Matrix& A, const Matrix& B);
    static Matrix transpose(const Matrix& A);
};

#endif