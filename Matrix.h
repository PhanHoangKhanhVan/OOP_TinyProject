#ifndef MATRIX_H
#define MATRIX_H

#include "Vector.h"

class Matrix {
private:
    int mNumRows, mNumCols;
    double** mData;

public:
    Matrix();                           
    Matrix(int rows, int cols);         
    Matrix(const Matrix& other);       
    ~Matrix();                         

    int Rows() const;
    int Cols() const;

    double& operator()(int i, int j);       
    double operator()(int i, int j) const;   

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
