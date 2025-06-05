// include/Vector.hpp
#ifndef VECTOR_HPP
#define VECTOR_HPP

class Vector {
private:
    int mSize;
    double* mData;

public:
    Vector(int size);
    Vector(const Vector& other);         // Copy constructor
    ~Vector();                           // Destructor

    Vector& operator=(const Vector& other);   // Assignment operator

    double& operator[](int index);            // 0-based index
    double& operator()(int index);            // 1-based index with check

    Vector operator+(const Vector& other) const;
    Vector operator-(const Vector& other) const;
    Vector operator*(double scalar) const;

    int size() const;
};

#endif
