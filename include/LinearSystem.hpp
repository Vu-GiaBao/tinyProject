#ifndef linearsystem_hhp
#define linearsystem_hhp

#include "Matrix.hpp"
#include "Vector.hpp"

class LinearSystem 
{
protected:
    int mSize;  // Số phương trình / Số ẩn
    Matrix* mpA;   
    Vector* mpb; 

    // Không cho phép tạo hệ phương trình không có đầu vào (ma trận A và vector b)
    LinearSystem() = delete;

private:
    LinearSystem(const LinearSystem&) = delete;  // Cấm sao chép đối tượng đã có
    LinearSystem& operator=(const LinearSystem&) = delete;  // Cấm gán đối tượng

public:
    LinearSystem(const Matrix& A, const Vector& b);
    virtual ~LinearSystem();

    virtual Vector Solve() const;  // Giải phương trình
};

#endif
