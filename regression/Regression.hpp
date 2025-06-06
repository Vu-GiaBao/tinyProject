#ifndef Regression_hpp
#define Regression_hpp
#include "Matrix.h"
#include "Vector.h"
#include <string>
#include <vector>

class Regression 
{
public:
    static Vector Fit(const Matrix& A, const Vector& b);
    static double RMSE(const Vector& y_pred, const Vector& y_true);
    static void read_csv(const std::string& filename, std::vector<std::vector<double>>& X, std::vector<double>& y);
};
#endif
