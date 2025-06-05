#include "../include/Vector.hpp"
#include <iostream>

int main() {
    Vector v1(3);
    v1(1) = 1.0;
    v1(2) = 2.0;
    v1(3) = 3.0;

    Vector v2 = v1 * 2.0;
    Vector v3 = v1 + v2;

    for (int i = 1; i <= v3.size(); ++i) {
        std::cout << "v3(" << i << ") = " << v3(i) << std::endl;
    }

    return 0;
}
