# Part A

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude -Iregression

# List of source files
VECTOR_SRC = src/Vector.cpp
MATRIX_SRC = src/Matrix.cpp
LINEAR_SRC = src/LinearSystem.cpp
POSSYM_SRC = src/PosSymLinSystem.cpp

# Test list
TEST_VECTOR = test/test_Vector.cpp
TEST_MATRIX = test/test_Matrix.cpp
TEST_LINEAR = test/test_LinearSystem.cpp
TEST_POSSYM = test/test_PosSym.cpp

# Output programs
BIN_VECTOR = test_vector
BIN_MATRIX = test_matrix
BIN_LINEAR = test_linear
BIN_POSSYM = test_possym

# Build target
all: $(BIN_VECTOR) $(BIN_MATRIX) $(BIN_LINEAR) $(BIN_POSSYM)

$(BIN_VECTOR): $(TEST_VECTOR) $(VECTOR_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BIN_MATRIX): $(TEST_MATRIX) $(MATRIX_SRC) $(VECTOR_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BIN_LINEAR): $(TEST_LINEAR) $(VECTOR_SRC) $(MATRIX_SRC) $(LINEAR_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BIN_POSSYM): $(TEST_POSSYM) $(POSSYM_SRC) $(LINEAR_SRC) $(MATRIX_SRC) $(VECTOR_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Run each test
run_vector:
	./$(BIN_VECTOR)

run_matrix:
	./$(BIN_MATRIX)

run_linear:
	./$(BIN_LINEAR)

run_possym:
	./$(BIN_POSSYM)

# Part B

regression_main: regression/regression_main.cpp regression/Regression.cpp $(VECTOR_SRC) $(MATRIX_SRC) $(LINEAR_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

run_regression:
	./regression_main

# Build all
BIN_VECTOR = test_vector
BIN_MATRIX = test_matrix
BIN_LINEAR = test_linear
BIN_POSSYM = test_possym
BIN_REGRESSION = regression_main

all: $(BIN_VECTOR) $(BIN_MATRIX) $(BIN_LINEAR) $(BIN_POSSYM) $(BIN_REGRESSION) 

run_all:
	./$(BIN_VECTOR)
	./$(BIN_MATRIX)
	./$(BIN_LINEAR)
	./$(BIN_POSSYM)
	./$(BIN_REGRESSION)
	
clean:
	rm -f test_vector test_matrix test_linear test_possym regression_main
