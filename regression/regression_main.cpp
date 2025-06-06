#include "Regression.hpp"
#include <iostream>

int main() {
    // Load dataset
    Matrix A;
    Vector b;
    Regression::LoadData("data/machine.data", A, b);
    std::cout << "Data loaded: " << A.numRows() << " samples, " << A.numCols() << " features\n";

    // Split into training and testing
    Matrix A_train, A_test;
    Vector b_train, b_test;
    Regression::TrainTestSplit(A, b, A_train, b_train, A_test, b_test);
    std::cout << "Training set: " << A_train.numRows() << " samples\n";
    std::cout << "Testing set: " << A_test.numRows() << " samples\n";

    // Solve for regression coefficients
    Vector x = Regression::SolveLinearRegression(A_train, b_train);
    std::cout << "Model trained. Coefficients:\n";
    for (int i = 1; i <= x.size(); ++i) {
        std::cout << "x(" << i << ") = " << x(i) << std::endl;
    }

    // Predict on test set
    Vector pred = A_test * x;

    // Evaluate
    double rmse = Regression::ComputeRMSE(b_test, pred);
    std::cout << "RMSE on test set: " << rmse << std::endl;

    return 0;
}
