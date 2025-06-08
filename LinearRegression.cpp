#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm> 
#include <cstdlib>  
#include "Matrix.h"
#include "Vector.h"

// Hàm tải dữ liệu từ file machine.data
std::pair<Matrix, Vector> LoadDataset(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Can not open file: " << filename << std::endl;
        exit(1);
    }

    std::string line;
    std::vector<std::vector<double>> features;
    std::vector<double> labels;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string token;

        for (int i = 0; i < 2; ++i) std::getline(ss, token, ',');

        std::vector<double> row;
        for (int i = 0; i < 6; ++i) {
            std::getline(ss, token, ',');
            row.push_back(std::stod(token));
        }

        std::getline(ss, token, ','); // PRP
        labels.push_back(std::stod(token));
        features.push_back(row);
    }

    std::cout << "Data can be read: " << features.size() << " line\n";

    int n = features.size();
    Matrix A(n, 7); 
    Vector b(n);

    for (int i = 0; i < n; ++i) {
        A(i + 1, 1) = 1.0; // bias
        for (int j = 0; j < 6; ++j)
            A(i + 1, j + 2) = features[i][j];
        b[i] = labels[i];
    }

    return {A, b};
}

void ShuffleDataset(Matrix& A, Vector& b) {
    int n = A.Rows();
    std::vector<int> indices(n);
    for (int i = 0; i < n; ++i) indices[i] = i;

    std::random_shuffle(indices.begin(), indices.end());

    Matrix A_shuffled(n, A.Cols());
    Vector b_shuffled(n);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < A.Cols(); ++j)
            A_shuffled(i + 1, j + 1) = A(indices[i] + 1, j + 1);
        b_shuffled[i] = b[indices[i]];
    }

    A = A_shuffled;
    b = b_shuffled;
}

void SplitTrainTest(const Matrix& A, const Vector& b,
                    Matrix& A_train, Vector& b_train,
                    Matrix& A_test, Vector& b_test) {
    int total = A.Rows();
    int train_size = static_cast<int>(total * 0.8);

    A_train = Matrix(train_size, A.Cols());
    b_train = Vector(train_size);
    A_test = Matrix(total - train_size, A.Cols());
    b_test = Vector(total - train_size);

    for (int i = 0; i < total; ++i) {
        for (int j = 0; j < A.Cols(); ++j) {
            if (i < train_size)
                A_train(i + 1, j + 1) = A(i + 1, j + 1);
            else
                A_test(i + 1 - train_size, j + 1) = A(i + 1, j + 1);
        }

        if (i < train_size)
            b_train[i] = b[i];
        else
            b_test[i - train_size] = b[i];
    }

    std::cout << "Train size: " << train_size << ", Test size: " << total - train_size << std::endl;
}

double RMSE(const Matrix& A, const Vector& b, const Vector& x) {
    Vector pred = A * x;
    double sum = 0.0;
    for (int i = 0; i < b.Size(); ++i)
        sum += (pred[i] - b[i]) * (pred[i] - b[i]);
    return std::sqrt(sum / b.Size());
}

int main() {
    auto [A, b] = LoadDataset("machine.data");

    ShuffleDataset(A, b); 

    Matrix A_train, A_test;
    Vector b_train, b_test;
    SplitTrainTest(A, b, A_train, b_train, A_test, b_test);

    Matrix A_pinv = A_train.PseudoInverse();
    Vector x = A_pinv * b_train;

    double train_rmse = RMSE(A_train, b_train, x);
    double test_rmse = RMSE(A_test, b_test, x);

    std::cout << "Train RMSE: " << train_rmse << std::endl;
    std::cout << "Test  RMSE: " << test_rmse << std::endl;

    return 0;
}
