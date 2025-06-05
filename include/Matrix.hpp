#ifndef matrix_hpp
#define matrix_hpp

#include <cassert>
#include <iostream>
#include "Vector.hpp"

class Matrix 
{
protected:
    int mNumRows;  // số hàng
    int mNumCols;  // số cột
    double** mData;

    void allocateMemory(int rows, int cols);   // cấp phát bộ nhớ cho mảng 2D
    void freeMemory();                        // giải phóng bộ nhớ

public:
    // Khởi tạo, xóa, sao lưu
    Matrix(int rows, int cols);     // tạo ma trận
    Matrix(const Matrix& other);   // copy
    ~Matrix();                    // xóa (giải phóng bộ nhớ)

    // Gán
    Matrix& operator=(const Matrix& other);

    // Truy cập phần tử
    int numRows() const { return mNumRows; }
    int numCols() const { return mNumCols; }
    double& operator()(int i, int j);
    const double& operator()(int i, int j) const;

    // Toán tử
    Matrix operator+() const;   // trả về bản sao
    Matrix operator-() const;  // trả về ma trận đối

    Matrix operator+(const Matrix& rhs) const;    // cộng 2 ma trận
    Matrix operator-(const Matrix& rhs) const;   // trừ 2 ma trận
    Matrix operator*(const Matrix& rhs) const;  // nhân 2 ma trận

    Matrix operator*(double scalar) const;                       // Ma trận nhân Số
    friend Matrix operator*(double scalar, const Matrix& mat);  // Số nhân Ma trận

    Vector operator*(const Vector& vec) const;  // Ma trận nhân Vector

    Matrix pseudoInverse() const;

    // Ma trận vuông
    double determinant() const;  // định thức
    Matrix inverse() const;     // đảo

    // Output 
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
};

#endif
