#include "../include/Matrix.hpp"
#include <iostream>

int main() {
    Matrix A(2, 2);
    A(1,1) = 4; A(1,2) = 7;
    A(2,1) = 2; A(2,2) = 6;

    std::cout << "Matrix A:\n";
    for (int i = 1; i <= 2; ++i) {
        for (int j = 1; j <= 2; ++j) {
            std::cout << A(i, j) << " ";
        }
        std::cout << "\n";
    }

    double det = A.determinant();
    std::cout << "Determinant: " << det << "\n";

    Matrix inv = A.inverse();
    std::cout << "Inverse matrix:\n";
    for (int i = 1; i <= 2; ++i) {
        for (int j = 1; j <= 2; ++j) {
            std::cout << inv(i, j) << " ";
        }
        std::cout << "\n";
    }

    return 0;
}
