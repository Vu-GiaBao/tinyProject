# TinyProject – Linear Algebra & Regression in C++

This project implements core numerical linear algebra components (vectors, matrices, and linear system solvers), and applies them to solve a real-world linear regression problem using a dataset from UCI.

---

## Part A – Vector, Matrix, and LinearSystem

### Features implemented:
- `Vector` class:
  - Dynamic memory
  - Operator overloading: `+`, `-`, `*`, `[]`, `()`
  - Bounds checking
- `Matrix` class:
  - Dynamic 2D array
  - Matrix arithmetic with vectors/scalars
  - `det()`, `inverse()`, `pseudoInverse()`
- `LinearSystem` class:
  - Solves `Ax = b` using Gaussian Elimination with pivoting
- `PosSymLinSystem` class (**bonus**):
  - Inherits from `LinearSystem`
  - Overrides `Solve()` using **Conjugate Gradient method**
  - Efficient for symmetric positive-definite matrices
- Unit tests provided in `test/` directory

---

## Part B – Linear Regression (UCI dataset)

- **Dataset**: [Computer Hardware Data](https://archive.ics.uci.edu/ml/datasets/Computer%2BHardware)
- **Model**:  
  PRP = x₁·MYCT + x₂·MMIN + x₃·MMAX + x₄·CACH + x₅·CHMIN + x₆·CHMAX
- **Goal**: Find best-fit coefficients `x₁...x₆` using least squares
- **Approach**: Solve system `AᵀA·x = Aᵀ·b` with methods from Part A
- **Evaluation**: Root Mean Square Error (RMSE) on test set
- **Split**:
  - 80% training
  - 20% testing

---

## How to Build

```bash
make                # Build all components (Part A + Part B)
```

---

## How to Run Tests (Part A)

```bash
make run_all        # Run all test cases and regression

# Or run individual test cases:
./test_vector       # Tests for Vector
./test_matrix       # Tests for Matrix
./test_linear       # Tests for LinearSystem
./test_possym       # Tests for PosSymLinSystem
```

---

## How to Run Regression (Part B)

```bash
make regression_main
./regression_main
```

Expected output includes:
- Number of samples loaded
- Train/test split info
- Coefficients of regression model
- RMSE on test set

---

## Clean up build files

```bash
make clean
```

Removes all executable files:
- `test_vector`
- `test_matrix`
- `test_linear`
- `test_possym`
- `regression_main`

---

## Project Structure

```
TinyProject/
├── data/                   # Dataset
│   └── machine.data
│
├── include/                # Header files (.hpp)
│   ├── LinearSystem.hpp
│   ├── Matrix.hpp
│   ├── PosSymLinSystem.hpp
│   └── Vector.hpp
│
├── regression/             # Regression logic (Part B)
│   ├── regression_main.cpp
│   ├── Regression.cpp
│   └── Regression.hpp
│
├── src/                    # Implementations (Part A)
│   ├── LinearSystem.cpp
│   ├── Matrix.cpp
│   ├── PosSymLinSystem.cpp
│   └── Vector.cpp
│
├── test/                   # Unit tests for Part A
│   ├── test_LinearSystem.cpp
│   ├── test_Matrix.cpp
│   ├── test_PosSym.cpp
│   └── test_Vector.cpp
│
├── Makefile                # Build instructions
└── README.md               # Project documentation
```

---

## Notes
- Code uses C++17 standard
- Dataset must be located in `data/machine.data`

---

## Authors
- **Group members:**
  - Vu Gia Bao – `10423014`
  - Nguyen Minh Phu – `10423090`
  - Le Huy Thinh – `10423105`
- **Course:** Programming 2 SS25  
- **Instructor:** Huynh Trung Hieu