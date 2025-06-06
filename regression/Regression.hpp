#ifndef REGRESSION_HPP
#define REGRESSION_HPP

#include "../include/Matrix.hpp"
#include "../include/Vector.hpp"

class Regression {
public:
  
    static void LoadData(const std::string& filename, Matrix& A, Vector& b);

    
    static void TrainTestSplit(const Matrix& A, const Vector& b,
                                Matrix& A_train, Vector& b_train,
                                Matrix& A_test, Vector& b_test,
                                double train_ratio = 0.8);

    static Vector SolveLinearRegression(const Matrix& A, const Vector& b);

    static double ComputeRMSE(const Vector& y_true, const Vector& y_pred);
};

#endif
