#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"

class Matrix {
private:
    int mNumRows, mNumCols;
    double** mData;

public:
    Matrix();                            // Constructor mặc định
    Matrix(int rows, int cols);         // Constructor khởi tạo
    Matrix(const Matrix& other);        // Copy constructor
    ~Matrix();                          // Destructor

    int Rows() const;
    int Cols() const;

    double& operator()(int i, int j);        // Truy cập 1-based
    double operator()(int i, int j) const;   // Const version

    Matrix& operator=(const Matrix& other);
    Matrix operator+(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Vector operator*(const Vector& vec) const;

    Matrix Transpose() const;
    Matrix PseudoInverse() const;
    double Determinant() const;
    Matrix Inverse() const;
};

#endif