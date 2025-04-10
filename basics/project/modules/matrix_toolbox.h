#pragma once


class Matrix{
    public:
        Matrix() = delete;
        Matrix(size_t row, size_t col);
        ~Matrix();

        void print() const;
        Matrix add(const Matrix&) const;
        Matrix multiply(const Matrix&) const;

    private:
        size_t cols;
        size_t rows;
        double** data;
};