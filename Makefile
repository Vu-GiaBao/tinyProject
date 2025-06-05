CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

test_vector: test/test_Vector.cpp src/Vector.cpp
	$(CXX) $(CXXFLAGS) -o test_vector test/test_Vector.cpp src/Vector.cpp

run_test:
	./test_vector
