#include "Matrix.h"
#include "LinearSystem.h"
#include <cassert>
#include <cmath>
#include <algorithm>

Matrix::Matrix() : mNumRows(0), mNumCols(0), mData(nullptr) {}

Matrix::Matrix(int rows, int cols) : mNumRows(rows), mNumCols(cols) {
    mData = new double*[mNumRows];
    for (int i = 0; i < mNumRows; ++i)
        mData[i] = new double[mNumCols]();
}

Matrix::Matrix(const Matrix& other) : mNumRows(other.mNumRows), mNumCols(other.mNumCols) {
    mData = new double*[mNumRows];
    for (int i = 0; i < mNumRows; ++i) {
        mData[i] = new double[mNumCols];
        for (int j = 0; j < mNumCols; ++j)
            mData[i][j] = other.mData[i][j];
    }
}

Matrix::~Matrix() {
    if (mData) {
        for (int i = 0; i < mNumRows; ++i)
            delete[] mData[i];
        delete[] mData;
    }
}

int Matrix::Rows() const {
    return mNumRows;
}

int Matrix::Cols() const {
    return mNumCols;
}

double& Matrix::operator()(int i, int j) {
    assert(i > 0 && i <= mNumRows && j > 0 && j <= mNumCols);
    return mData[i - 1][j - 1];
}

double Matrix::operator()(int i, int j) const {
    assert(i > 0 && i <= mNumRows && j > 0 && j <= mNumCols);
    return mData[i - 1][j - 1];
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        for (int i = 0; i < mNumRows; ++i)
            delete[] mData[i];
        delete[] mData;

        mNumRows = other.mNumRows;
        mNumCols = other.mNumCols;
        mData = new double*[mNumRows];
        for (int i = 0; i < mNumRows; ++i) {
            mData[i] = new double[mNumCols];
            for (int j = 0; j < mNumCols; ++j)
                mData[i][j] = other.mData[i][j];
        }
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix& other) const {
    assert(mNumRows == other.mNumRows && mNumCols == other.mNumCols);
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result(i + 1, j + 1) = mData[i][j] + other.mData[i][j];
    return result;
}

Matrix Matrix::operator*(const Matrix& other) const {
    assert(mNumCols == other.mNumRows);
    Matrix result(mNumRows, other.mNumCols);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < other.mNumCols; ++j)
            for (int k = 0; k < mNumCols; ++k)
                result(i + 1, j + 1) += mData[i][k] * other.mData[k][j];
    return result;
}

Vector Matrix::operator*(const Vector& vec) const {
    assert(mNumCols == vec.Size());
    Vector result(mNumRows);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            result[i] += mData[i][j] * vec(j + 1);
    return result;
}

Matrix Matrix::Transpose() const {
    Matrix T(mNumCols, mNumRows);
    for (int i = 0; i < mNumRows; ++i)
        for (int j = 0; j < mNumCols; ++j)
            T(j + 1, i + 1) = mData[i][j];
    return T;
}

Matrix Matrix::PseudoInverse() const {
    Matrix A_T = this->Transpose();
    Matrix AtA = A_T * (*this);
    int n = AtA.Rows();
    Matrix inv(n, n);
    for (int i = 0; i < n; ++i) {
        Vector b(n);
        b[i] = 1;
        LinearSystem sys(AtA, b);
        Vector col = sys.Solve();
        for (int j = 0; j < n; ++j)
            inv(j + 1, i + 1) = col(j + 1);
    }
    return inv * A_T;
}

double Matrix::Determinant() const {
    assert(mNumRows == mNumCols);
    Matrix temp(*this);
    int n = mNumRows;
    double det = 1.0;

    for (int k = 0; k < n; ++k) {
        int maxRow = k;
        for (int i = k + 1; i < n; ++i)
            if (std::fabs(temp(i + 1, k + 1)) > std::fabs(temp(maxRow + 1, k + 1)))
                maxRow = i;

        if (k != maxRow) {
            for (int j = 0; j < n; ++j)
                std::swap(temp(k + 1, j + 1), temp(maxRow + 1, j + 1));
            det *= -1;
        }

        det *= temp(k + 1, k + 1);
        if (std::fabs(temp(k + 1, k + 1)) < 1e-12)
            return 0;

        for (int i = k + 1; i < n; ++i) {
            double factor = temp(i + 1, k + 1) / temp(k + 1, k + 1);
            for (int j = k; j < n; ++j)
                temp(i + 1, j + 1) -= factor * temp(k + 1, j + 1);
        }
    }
    return det;
}


Matrix Matrix::Inverse() const {
    assert(mNumRows == mNumCols);
    int n = mNumRows;
    Matrix aug(n, 2 * n);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            aug(i + 1, j + 1) = mData[i][j];
            aug(i + 1, j + 1 + n) = (i == j) ? 1.0 : 0.0;
        }

    for (int i = 0; i < n; ++i) {
        double pivot = aug(i + 1, i + 1);
        assert(std::fabs(pivot) > 1e-12);
        for (int j = 0; j < 2 * n; ++j)
            aug(i + 1, j + 1) /= pivot;

        for (int k = 0; k < n; ++k) {
            if (k == i) continue;
            double factor = aug(k + 1, i + 1);
            for (int j = 0; j < 2 * n; ++j)
                aug(k + 1, j + 1) -= factor * aug(i + 1, j + 1);
        }
    }

    Matrix inv(n, n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            inv(i + 1, j + 1) = aug(i + 1, j + 1 + n);
    return inv;
}
