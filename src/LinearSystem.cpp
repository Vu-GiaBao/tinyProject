#include "LinearSystem.hpp"
#include <cassert>
#include <cmath>
#include <algorithm>
using namespace std;

LinearSystem::LinearSystem(const Matrix& A, const Vector& b)    // Constructor 
{
    assert(A.numRows() == A.numCols());
    assert(A.numRows() == b.size());
    mSize = A.numRows();
    mpA = new Matrix(A);
    mpb = new Vector(b);
}

LinearSystem::~LinearSystem()   // Destructor 
{
    delete mpA;
    delete mpb;
}

Vector LinearSystem::Solve()    // Giải hệ bằng phương pháp khử Gauss 
{
    Matrix A(*mpA);
    Vector b(*mpb);
    int n = mSize;

    for (int i = 0; i < n; ++i) // Khử Gauss 
    {
        int pivot = i;  // Chọn pivot
        for (int j = i + 1; j < n; ++j)
            if (fabs(A(j + 1, i + 1)) > fabs(A(pivot + 1, i + 1)))
                pivot = j;

        for (int k = 1; k <= n; ++k)    // hoán vị
            swap(A(i + 1, k), A(pivot + 1, k));
        swap(b[i], b[pivot]);

        double pivotVal = A(i + 1, i + 1);  // kiểm tra pivot (=0?)
        assert(pivotVal != 0);

        for (int j = i + 1; j < n; ++j) 
        {
            double factor = A(j + 1, i + 1) / pivotVal; // Khử Gauss
            for (int k = i + 1; k <= n; ++k)
                A(j + 1, k) -= factor * A(i + 1, k);
            b[j] -= factor * b[i];
        }
    }

    Vector x(n);    // Giải ngược
    for (int i = n - 1; i >= 0; --i) 
    {
        x[i] = b[i];
        for (int j = i + 1; j < n; ++j)
            x[i] -= A(i + 1, j + 1) * x[j];
        x[i] /= A(i + 1, i + 1);
    }
    return x;
}

