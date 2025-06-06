#include "Regression.hpp"
#include <cmath>
#include <cassert>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

Vector Regression::Fit(const Matrix& A, const Vector& b)    // hồi quy tuyến tính
{
    Matrix A_pinv = A.pseudoInverse();
    return A_pinv * b;
}

double Regression::RMSE(const Vector& y_pred, const Vector& y_true) // Root Mean Squared Error (RMSE)
{
    assert(y_pred.GetSize() == y_true.GetSize());
    double sum = 0.0;                               // tổng bình phương sai số
    for (int i = 0; i < y_pred.GetSize(); ++i)
        sum += pow(y_pred[i] - y_true[i], 2);
    return sqrt(sum / y_pred.GetSize());
}

void Regression::read_csv(const string& filename, vector<vector<double>>& X, vector<double>& y) 
{
    ifstream file(filename);                                                                    // mở file + kiểm tra
    if (!file.is_open()) 
    {
        cerr << "Failed to open file: " << filename << "\n";
        return;
    }
    string line;    // đọc
    while (getline(file, line)) 
    {
        stringstream ss(line);  // tách dòng
        string token;
        vector<double> numeric_values;
        while (getline(ss, token, ',')) 
        {
            try 
            {
                numeric_values.push_back(stod(token));
            } catch (...) {

            }
        }
        if (numeric_values.size() >= 9) // lọc cột 
        {
            vector<double> features(numeric_values.begin(), numeric_values.begin() + 8);    // tách features
            double target = numeric_values[8];  // lấy target
            X.push_back(features);
            y.push_back(target);
        }
    }
    file.close();
}



