#ifndef matrix_hpp
#define matrix_hpp
#include <cassert>
#include <iostream>
#include "Vector.hpp"

class Matrix 
{
protected:
    int mNumRows;  
    int mNumCols;  
    double** mData;

    void allocateMemory(int rows, int cols);   
    void freeMemory();                        

public:
    Matrix(); 
    Matrix(int rows, int cols);    
    Matrix(const Matrix& other);   
    ~Matrix();                    

    
    Matrix& operator=(const Matrix& other);

    
    int numRows() const { return mNumRows; }
    int numCols() const { return mNumCols; }
    double& operator()(int i, int j);
    const double& operator()(int i, int j) const;

    Matrix transpose() const;
    Matrix operator+() const;   
    Matrix operator-() const;  

    Matrix operator+(const Matrix& rhs) const;    
    Matrix operator-(const Matrix& rhs) const;  
    Matrix operator*(const Matrix& rhs) const;  
    Matrix operator*(double scalar) const;                      
    friend Matrix operator*(double scalar, const Matrix& mat);  

    Vector operator*(const Vector& vec) const;  

    Matrix pseudoInverse() const;

   
    double determinant() const;  
    Matrix inverse() const;     

    // Output 
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
};

#endif
