#include "PosSymLinSystem.hpp"
#include <cmath>
#include <cassert>

PosSymLinSystem::PosSymLinSystem(const Matrix& A, const Vector& b)
    : LinearSystem(A, b) {
    // Optional: check symmetry of A
    assert(A.numRows() == A.numCols());
}

Vector PosSymLinSystem::Solve() const {
    int n = mSize;
    Vector x(n); // initialized to 0
    Vector r = *mpb - (*mpA * x);
    Vector p = r;
    double rsold = r * r;

    for (int i = 0; i < 1000; ++i) {
        Vector Ap = (*mpA) * p;
        double alpha = rsold / (p * Ap);
        x = x + p * alpha;
        r = r - Ap * alpha;

        double rsnew = r * r;
        if (std::sqrt(rsnew) < 1e-10)
            break;

        p = r + p * (rsnew / rsold);
        rsold = rsnew;
    }

    return x;
}
