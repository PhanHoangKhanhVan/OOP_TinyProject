#include <iostream>
#include "Matrix.h"
#include "Vector.h"
#include "LinearSystem.h"

void InputMatrix(Matrix& M) {
    int rows = M.Rows();
    int cols = M.Cols();
    std::cout << "Nhập ma trận " << rows << "x" << cols << ":\n";
    for (int i = 1; i <= rows; ++i)
        for (int j = 1; j <= cols; ++j) {
            std::cout << "M(" << i << "," << j << "): ";
            std::cin >> M(i, j);
        }
}

void InputVector(Vector& v) {
    int n = v.Size();
    std::cout << "Nhập vector kích thước " << n << ":\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "v[" << i + 1 << "]: ";
        std::cin >> v[i];
    }
}

int main() {
    std::cout << "Thử nghiệm các phép toán với Matrix & Vector\n";

    int m, n;
    std::cout << "Nhập số hàng của ma trận A: ";
    std::cin >> m;
    std::cout << "Nhập số cột của ma trận A: ";
    std::cin >> n;

    Matrix A(m, n);
    InputMatrix(A);

    std::cout << "\nMa trận A bạn vừa nhập là:\n";
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j)
            std::cout << A(i, j) << " ";
        std::cout << std::endl;
    }

    // Nếu là ma trận vuông thì thử nghịch đảo và định thức
    if (m == n) {
        double det = A.Determinant();
        std::cout << "Định thức của A là: " << det << std::endl;

        if (std::fabs(det) > 1e-6) {
            Matrix A_inv = A.Inverse();
            std::cout << "Nghịch đảo của A là:\n";
            for (int i = 1; i <= m; ++i) {
                for (int j = 1; j <= n; ++j)
                    std::cout << A_inv(i, j) << " ";
                std::cout << std::endl;
            }
        } else {
            std::cout << "A không khả nghịch (det gần 0)\n";
        }
    }

    // Thử giải hệ phương trình Ax = b
    if (m == n) {
        Vector b(m);
        InputVector(b);

        LinearSystem sys(A, b);
        Vector x = sys.Solve();

        std::cout << "Nghiệm x của hệ Ax = b là:\n";
        x.Print();
    }

    return 0;
}