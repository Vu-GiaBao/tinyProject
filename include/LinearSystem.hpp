#ifndef LINEARSYSTEM_HPP
#define LINEARSYSTEM_HPP

#include "Matrix.hpp"
#include "Vector.hpp"

class LinearSystem {
protected:
    int mSize;
    Matrix* mpA;
    Vector* mpb;

public:
    LinearSystem(const Matrix& A, const Vector& b);
    virtual ~LinearSystem();

    virtual Vector Solve() const;
};

#endif
