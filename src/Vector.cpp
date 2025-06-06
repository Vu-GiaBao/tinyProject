// src/Vector.cpp
#include "../include/Vector.hpp"

Vector::Vector(int size) : mSize(size) {
    mData = new double[mSize]{};
}

Vector::Vector(const Vector& other) : mSize(other.mSize) {
    mData = new double[mSize];
    for (int i = 0; i < mSize; ++i) {
        mData[i] = other.mData[i];
    }
}

Vector::~Vector() {
    delete[] mData;
}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        delete[] mData;
        mSize = other.mSize;
        mData = new double[mSize];
        for (int i = 0; i < mSize; ++i) {
            mData[i] = other.mData[i];
        }
    }
    return *this;
}

// 0-based index, non-const
double& Vector::operator[](int index) {
    assert(index >= 0 && index < mSize);
    return mData[index];
}

// 0-based index, const version
double Vector::operator[](int index) const {
    assert(index >= 0 && index < mSize);
    return mData[index];
}

// 1-based index with check
double& Vector::operator()(int index) {
    if (index < 1 || index > mSize) {
        throw std::out_of_range("Index out of bounds (1-based)");
    }
    return mData[index - 1];
}

// Vector + Vector
Vector Vector::operator+(const Vector& other) const {
    assert(mSize == other.mSize);
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result.mData[i] = mData[i] + other.mData[i];
    return result;
}

// Vector - Vector
Vector Vector::operator-(const Vector& other) const {
    assert(mSize == other.mSize);
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result.mData[i] = mData[i] - other.mData[i];
    return result;
}

// Vector * scalar
Vector Vector::operator*(double scalar) const {
    Vector result(mSize);
    for (int i = 0; i < mSize; ++i)
        result.mData[i] = mData[i] * scalar;
    return result;
}

int Vector::size() const {
    return mSize;
}
