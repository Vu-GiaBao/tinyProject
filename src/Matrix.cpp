#include "Matrix.hpp"
#include <algorithm>
#include <iostream>
#include <cmath>
#include <cassert>

void Matrix::allocateMemory(int rows, int cols) {
    mData = new double*[rows];
    for (int i = 0; i < rows; ++i) {
        mData[i] = new double[cols]();
    }
}

void Matrix::freeMemory() {
    if (mData) {
        for (int i = 0; i < mNumRows; ++i) {
            delete[] mData[i];
        }
        delete[] mData;
        mData = nullptr;
    }
}

Matrix::Matrix(int rows, int cols) : mNumRows(rows), mNumCols(cols) {
    assert(rows > 0 && cols > 0);
    allocateMemory(mNumRows, mNumCols);
}

Matrix::Matrix(const Matrix& other) : mNumRows(other.mNumRows), mNumCols(other.mNumCols) {
    allocateMemory(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i) {
        std::copy(other.mData[i], other.mData[i] + mNumCols, mData[i]);
    }
}

Matrix::~Matrix() {
    freeMemory();
}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this == &other) return *this;

    if (mNumRows != other.mNumRows || mNumCols != other.mNumCols) {
        freeMemory();
        mNumRows = other.mNumRows;
        mNumCols = other.mNumCols;
        allocateMemory(mNumRows, mNumCols);
    }

    for (int i = 0; i < mNumRows; ++i) {
        std::copy(other.mData[i], other.mData[i] + mNumCols, mData[i]);
    }
    return *this;
}

double& Matrix::operator()(int i, int j) {
    assert(i >= 1 && i <= mNumRows);
    assert(j >= 1 && j <= mNumCols);
    return mData[i - 1][j - 1];
}

const double& Matrix::operator()(int i, int j) const {
    assert(i >= 1 && i <= mNumRows);
    assert(j >= 1 && j <= mNumCols);
    return mData[i - 1][j - 1];
}

Matrix Matrix::operator+() const {
    return *this;
}

Matrix Matrix::operator-() const {
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i) {
        for (int j = 0; j < mNumCols; ++j) {
            result.mData[i][j] = -mData[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator+(const Matrix& rhs) const {
    assert(mNumRows == rhs.mNumRows && mNumCols == rhs.mNumCols);
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i) {
        for (int j = 0; j < mNumCols; ++j) {
            result.mData[i][j] = mData[i][j] + rhs.mData[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix& rhs) const {
    assert(mNumRows == rhs.mNumRows && mNumCols == rhs.mNumCols);
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i) {
        for (int j = 0; j < mNumCols; ++j) {
            result.mData[i][j] = mData[i][j] - rhs.mData[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix& rhs) const {
    assert(mNumCols == rhs.mNumRows);
    Matrix result(mNumRows, rhs.mNumCols);
    for (int i = 0; i < mNumRows; ++i) {
        for (int j = 0; j < rhs.mNumCols; ++j) {
            double sum = 0.0;
            for (int k = 0; k < mNumCols; ++k) {
                sum += mData[i][k] * rhs.mData[k][j];
            }
            result.mData[i][j] = sum;
        }
    }
    return result;
}

Matrix Matrix::operator*(double scalar) const {
    Matrix result(mNumRows, mNumCols);
    for (int i = 0; i < mNumRows; ++i) {
        for (int j = 0; j < mNumCols; ++j) {
            result.mData[i][j] = mData[i][j] * scalar;
        }
    }
    return result;
}

Matrix operator*(double scalar, const Matrix& mat) {
    return mat * scalar;
}

Vector Matrix::operator*(const Vector& vec) const {
    assert(mNumCols == vec.size());
    Vector result(mNumRows);
    for (int i = 0; i < mNumRows; ++i) {
        double sum = 0.0;
        for (int j = 0; j < mNumCols; ++j) {
            sum += mData[i][j] * vec[j];
        }
        result[i] = sum;
    }
    return result;
}

static double determinantRecursive(double** data, int n) {
    if (n == 1) return data[0][0];
    if (n == 2) return data[0][0]*data[1][1] - data[0][1]*data[1][0];

    double det = 0.0;
    double** submatrix = new double*[n-1];
    for (int i = 0; i < n-1; ++i) {
        submatrix[i] = new double[n-1];
    }

    for (int x = 0; x < n; ++x) {
        // Ma trận con
        for (int i = 1; i < n; ++i) {
            int sub_j = 0;
            for (int j = 0; j < n; ++j) {
                if (j == x) continue;
                submatrix[i-1][sub_j] = data[i][j];
                ++sub_j;
            }
        }
        double subdet = determinantRecursive(submatrix, n-1);
        det += (x % 2 == 0 ? 1 : -1) * data[0][x] * subdet;
    }

    for (int i = 0; i < n-1; ++i) {
        delete[] submatrix[i];
    }
    delete[] submatrix;

    return det;
}

double Matrix::determinant() const {
    assert(mNumRows == mNumCols);
    return determinantRecursive(mData, mNumRows);
}


Matrix Matrix::inverse() const {
    assert(mNumRows == mNumCols);

    int n = mNumRows;
    Matrix augmented(n, 2 * n);

    // Ma trận tăng cường
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            augmented.mData[i][j] = mData[i][j];
        }
        for (int j = n; j < 2*n; ++j) {
            augmented.mData[i][j] = (j - n == i) ? 1.0 : 0.0;
        }
    }


    for (int i = 0; i < n; ++i) {
        // Phần tử trục (pivot)
        int maxRow = i;
        for (int k = i + 1; k < n; ++k) {
            if (fabs(augmented.mData[k][i]) > fabs(augmented.mData[maxRow][i])) {
                maxRow = k;
            }
        }
        if (maxRow != i) {
            std::swap(augmented.mData[i], augmented.mData[maxRow]);
        }

        // (pivot=0 or not)
        if (fabs(augmented.mData[i][i]) < 1e-14) {
            throw std::runtime_error("Matrix is singular, cannot invert");
        }

        // (pivot=1)
        double pivot = augmented.mData[i][i];
        for (int j = 0; j < 2 * n; ++j) {
            augmented.mData[i][j] /= pivot;
        }

        // Eliminate other rows
        for (int r = 0; r < n; ++r) {
            if (r == i) continue;
            double factor = augmented.mData[r][i];
            for (int c = 0; c < 2*n; ++c) {
                augmented.mData[r][c] -= factor * augmented.mData[i][c];
            }
        }
    }

    Matrix inv(n, n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inv.mData[i][j] = augmented.mData[i][j + n];
        }
    }
    return inv;
}


Matrix Matrix::pseudoInverse() const {
    // Use formula: A^+ = (A^T A)^-1 A^T
    Matrix At(mNumCols, mNumRows);
    // Transpose
    for (int i = 1; i <= mNumRows; ++i)
        for (int j = 1; j <= mNumCols; ++j)
            At(j,i) = (*this)(i,j);

    Matrix AtA = At * (*this);
    Matrix AtA_inv = AtA.inverse();
    return AtA_inv * At;
}

std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    for (int i = 0; i < m.mNumRows; ++i) {
        for (int j = 0; j < m.mNumCols; ++j) {
            os << m.mData[i][j] << " ";
        }
        os << "\n";
    }
    return os;
}

Matrix::Matrix() {
    mNumRows = 0;
    mNumCols = 0;
    mData = nullptr;
}

Matrix Matrix::transpose() const {
    Matrix result(mNumCols, mNumRows);
    for (int i = 1; i <= mNumRows; ++i) {
        for (int j = 1; j <= mNumCols; ++j) {
            result(j, i) = (*this)(i, j);
        }
    }
    return result;
}
