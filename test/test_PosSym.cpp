#include "PosSymLinSystem.hpp"
#include <iostream>

int main() {
    // Example symmetric positive definite matrix
    Matrix A(2, 2);
    A(1,1) = 4; A(1,2) = 1;
    A(2,1) = 1; A(2,2) = 3;

    Vector b(2);
    b(1) = 1;
    b(2) = 2;

    PosSymLinSystem system(A, b);
    Vector x = system.Solve();

    std::cout << "Solution using Conjugate Gradient:\n";
    for (int i = 1; i <= x.size(); ++i) {
        std::cout << "x(" << i << ") = " << x(i) << "\n";
    }

    return 0;
}
