#include "Regression.hpp"
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include "../include/LinearSystem.hpp"

void Regression::LoadData(const std::string& filename, Matrix& A, Vector& b) {
    std::ifstream infile(filename);
    std::string line;
    std::vector<std::vector<double>> features;
    std::vector<double> targets;

    while (std::getline(infile, line)) {
        std::stringstream ss(line);
        std::string token;
        std::vector<double> row;

        int col = 0;
        while (std::getline(ss, token, ',')) {
            if (col >= 2 && col <= 7) { // MYCT, MMIN, MMAX, CACH, CHMIN, CHMAX
                row.push_back(std::stod(token));
            }
            if (col == 8) { // PRP
                targets.push_back(std::stod(token));
            }
            col++;
        }
        features.push_back(row);
    }

    int rows = features.size();
    int cols = features[0].size();
    A = Matrix(rows, cols);
    b = Vector(rows);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            A(i + 1, j + 1) = features[i][j];
        }
        b(i + 1) = targets[i];
    }
}

void Regression::TrainTestSplit(const Matrix& A, const Vector& b,
                                Matrix& A_train, Vector& b_train,
                                Matrix& A_test, Vector& b_test,
                                double train_ratio) {
    int total = A.numRows();
    std::vector<int> indices(total);
    for (int i = 0; i < total; ++i) indices[i] = i;
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(indices.begin(), indices.end(), g);

    int train_size = static_cast<int>(total * train_ratio);
    int test_size = total - train_size;
    int cols = A.numCols();

    A_train = Matrix(train_size, cols);
    b_train = Vector(train_size);
    A_test = Matrix(test_size, cols);
    b_test = Vector(test_size);

    for (int i = 0; i < train_size; ++i) {
        for (int j = 0; j < cols; ++j)
            A_train(i + 1, j + 1) = A(indices[i] + 1, j + 1);
        b_train(i + 1) = b(indices[i] + 1);
    }

    for (int i = 0; i < test_size; ++i) {
        for (int j = 0; j < cols; ++j)
            A_test(i + 1, j + 1) = A(indices[train_size + i] + 1, j + 1);
        b_test(i + 1) = b(indices[train_size + i] + 1);
    }
}

Vector Regression::SolveLinearRegression(const Matrix& A, const Vector& b) {
    Matrix At = A.transpose();
    Matrix AtA = At * A;
    Vector Atb = At * b;

    LinearSystem sys(AtA, Atb);
    return sys.Solve();
}

double Regression::ComputeRMSE(const Vector& y_true, const Vector& y_pred) {
    assert(y_true.size() == y_pred.size());
    double sum = 0.0;
    for (int i = 0; i < y_true.size(); ++i) {
        double diff = y_true[i] - y_pred[i];
        sum += diff * diff;
    }
    return std::sqrt(sum / y_true.size());
}
