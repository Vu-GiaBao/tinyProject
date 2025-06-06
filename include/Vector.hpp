// include/Vector.hpp
#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cassert>
#include <stdexcept>

class Vector {
private:
    int mSize;
    double* mData;

public:
    // Constructor & Destructor
    Vector(int size);
    Vector(const Vector& other);              // Copy constructor
    ~Vector();                                // Destructor

    // Assignment operator
    Vector& operator=(const Vector& other);

    // Access operators
    double& operator[](int index);            // 0-based indexing (non-const)
    double operator[](int index) const;       // 0-based indexing (const)

    double& operator()(int index);            // 1-based indexing with check

    // Arithmetic
    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(double scalar) const;

    // Utility
    int size() const;
};

#endif
