#include "LinearSystem.h"
#include <cmath>
#include <algorithm>
#include <cassert>

LinearSystem::LinearSystem(Matrix& A, Vector& b)
    : mSize(A.Rows()), mpA(new Matrix(A)), mpb(new Vector(b)) {}

LinearSystem::~LinearSystem() {
    delete mpA;
    delete mpb;
}

Vector LinearSystem::Solve() {
    Matrix& A = *mpA;
    Vector& b = *mpb;
    int n = mSize;
    Matrix aug(n, n + 1);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            aug(i + 1, j + 1) = A(i + 1, j + 1);
        aug(i + 1, n + 1) = b(i + 1);
    }

    for (int k = 0; k < n; ++k) {
        int maxRow = k;
        for (int i = k + 1; i < n; ++i)
            if (std::fabs(aug(i + 1, k + 1)) > std::fabs(aug(maxRow + 1, k + 1)))
                maxRow = i;
        for (int j = 0; j <= n; ++j)
            std::swap(aug(k + 1, j + 1), aug(maxRow + 1, j + 1));

        for (int i = k + 1; i < n; ++i) {
            double factor = aug(i + 1, k + 1) / aug(k + 1, k + 1);
            for (int j = k; j <= n; ++j)
                aug(i + 1, j + 1) -= factor * aug(k + 1, j + 1);
        }
    }

    Vector x(n);
    for (int i = n - 1; i >= 0; --i) {
        x[i] = aug(i + 1, n + 1);
        for (int j = i + 1; j < n; ++j)
            x[i] -= aug(i + 1, j + 1) * x[j];
        x[i] /= aug(i + 1, i + 1);
    }

    return x;
}

PosSymLinSystem::PosSymLinSystem(Matrix& A, Vector& b) : LinearSystem(A, b) {
    assert(IsSymmetric(*mpA) && "Matrix is not symmetric!");
}

bool PosSymLinSystem::IsSymmetric(const Matrix& A) {
    for (int i = 1; i <= A.Rows(); ++i)
        for (int j = 1; j <= A.Cols(); ++j)
            if (A(i, j) != A(j, i))
                return false;
    return true;
}

Vector PosSymLinSystem::Solve() {
    const int n = mSize;
    Matrix& A = *mpA;
    Vector& b = *mpb;

    Vector x(n);
    Vector r = b - A * x;
    Vector p = r;
    Vector Ap(n);

    double rs_old = 0.0;
    for (int i = 0; i < n; ++i)
        rs_old += r[i] * r[i];

    for (int k = 0; k < n; ++k) {
        Ap = A * p;
        double dot = 0.0;
        for (int i = 0; i < n; ++i)
            dot += p[i] * Ap[i];

        double alpha = rs_old / dot;

        for (int i = 0; i < n; ++i)
            x[i] += alpha * p[i];

        for (int i = 0; i < n; ++i)
            r[i] -= alpha * Ap[i];

        double rs_new = 0.0;
        for (int i = 0; i < n; ++i)
            rs_new += r[i] * r[i];

        if (std::sqrt(rs_new) < 1e-10)
            break;

        for (int i = 0; i < n; ++i)
            p[i] = r[i] + (rs_new / rs_old) * p[i];

        rs_old = rs_new;
    }

    return x;
}