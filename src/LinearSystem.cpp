#include "../include/LinearSystem.hpp"
#include <cassert>
#include <cmath>
#include <algorithm>  // for std::swap

LinearSystem::LinearSystem(const Matrix& A, const Vector& b) {
    assert(A.numRows() == A.numCols());
    assert(A.numRows() == b.size());

    mSize = A.numRows();
    mpA = new Matrix(A);
    mpb = new Vector(b);
}

LinearSystem::~LinearSystem() {
    delete mpA;
    delete mpb;
}

Vector LinearSystem::Solve() const {
    Matrix A = *mpA;
    Vector b = *mpb;
    int n = mSize;

    for (int i = 1; i <= n; ++i) {
        // Pivoting
        int maxRow = i;
        for (int k = i + 1; k <= n; ++k) {
            if (std::abs(A(k, i)) > std::abs(A(maxRow, i)))
                maxRow = k;
        }

        for (int j = 1; j <= n; ++j)
            std::swap(A(i, j), A(maxRow, j));
        std::swap(b(i), b(maxRow));

        // Elimination
        for (int k = i + 1; k <= n; ++k) {
            double factor = A(k, i) / A(i, i);
            for (int j = i; j <= n; ++j)
                A(k, j) -= factor * A(i, j);
            b(k) -= factor * b(i);
        }
    }

    // Back substitution
    Vector x(n);
    for (int i = n; i >= 1; --i) {
        double sum = 0.0;
        for (int j = i + 1; j <= n; ++j)
            sum += A(i, j) * x(j);
        x(i) = (b(i) - sum) / A(i, i);
    }

    return x;
}
