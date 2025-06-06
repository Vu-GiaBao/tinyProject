# Makefile for Tiny Project - Part A

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

# List of source files
VECTOR_SRC = src/Vector.cpp
MATRIX_SRC = src/Matrix.cpp
LINEAR_SRC = src/LinearSystem.cpp

# Test list
TEST_VECTOR = test/test_Vector.cpp
TEST_MATRIX = test/test_Matrix.cpp
TEST_LINEAR = test/test_LinearSystem.cpp

# Output programs
BIN_VECTOR = test_vector
BIN_MATRIX = test_matrix
BIN_LINEAR = test_linear

# Build target
all: $(BIN_VECTOR) $(BIN_MATRIX) $(BIN_LINEAR)

$(BIN_VECTOR): $(TEST_VECTOR) $(VECTOR_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BIN_MATRIX): $(TEST_MATRIX) $(MATRIX_SRC) $(VECTOR_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BIN_LINEAR): $(TEST_LINEAR) $(VECTOR_SRC) $(MATRIX_SRC) $(LINEAR_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Run each test
run_vector:
	./$(BIN_VECTOR)

run_matrix:
	./$(BIN_MATRIX)

run_linear:
	./$(BIN_LINEAR)

clean:
	rm -f $(BIN_VECTOR) $(BIN_MATRIX) $(BIN_LINEAR)

test_LinearSystem: test_linear
