#include <iostream>
#include "Matrix.h"
#include "Vector.h"
#include "LinearSystem.h"

void InputMatrix(Matrix& M) {
    int rows = M.Rows();
    int cols = M.Cols();
    std::cout << "Input matrix " << rows << "x" << cols << ":\n";
    for (int i = 1; i <= rows; ++i)
        for (int j = 1; j <= cols; ++j) {
            std::cout << "M(" << i << "," << j << "): ";
            std::cin >> M(i, j);
        }
}

void InputVector(Vector& v) {
    int n = v.Size();
    std::cout << "Input Vector " << n << ":\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "v[" << i + 1 << "]: ";
        std::cin >> v[i];
    }
}

int main() {
    int m, n;
    std::cout << "Input row of A: ";
    std::cin >> m;
    std::cout << "Input column of A: ";
    std::cin >> n;

    Matrix A(m, n);
    InputMatrix(A);

    std::cout << "\nMatrix A:\n";
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j)
            std::cout << A(i, j) << " ";
        std::cout << std::endl;
    }

    if (m == n) {
        double det = A.Determinant();
        std::cout << "Dererminant of A: " << det << std::endl;

        if (std::fabs(det) > 1e-6) {
            Matrix A_inv = A.Inverse();
            std::cout << "Inverse of A:\n";
            for (int i = 1; i <= m; ++i) {
                for (int j = 1; j <= n; ++j)
                    std::cout << A_inv(i, j) << " ";
                std::cout << std::endl;
            }
        } else {
            std::cout << "A is not reversilble.\n";
        }
    }

    if (m == n) {
        Vector b(m);
        InputVector(b);

        LinearSystem sys(A, b);
        Vector x = sys.Solve();

        std::cout << "x = \n";
        x.Print();
    }

    return 0;
}
