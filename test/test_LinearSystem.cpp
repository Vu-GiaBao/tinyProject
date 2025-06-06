#include "../include/LinearSystem.hpp"
#include <iostream>

int main() {
    Matrix A(2, 2);
    A(1,1) = 2; A(1,2) = 1;
    A(2,1) = 5; A(2,2) = 7;

    Vector b(2);
    b(1) = 11;
    b(2) = 13;

    LinearSystem sys(A, b);
    Vector x = sys.Solve();

    std::cout << "Solution x:\n";
    for (int i = 1; i <= x.size(); ++i) {
        std::cout << "x(" << i << ") = " << x(i) << std::endl;
    }

    return 0;
}
