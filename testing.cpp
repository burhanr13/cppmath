#include "matrix.hpp"
// #include "polynomial.hpp"
#include "vector.hpp"
#include <iostream>

int main() {

    linalg::matrix a = {{1, 2, 4, 5}, {3, 4, 6, 4}, {2, 6, 7, 8}};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            a[i][j] = i * 4 + j;
        }
    }

    linalg::matrix b;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            b[i][j] = i * 3 + j;
        }
    }

    std::cout << a << '\n' << b;
    std::cout << a * b << '\n';
    std::cout << a + a << '\n';
    std::cout << 5 * a << '\n';
    a[0] += a[2];
    std::cout << a << '\n';
    std::cout << a.T() << '\n';

    linalg::vector v1 = {1, 2, 3};
    linalg::vector v2 = 2 * v1;
    linalg::vector v3 = v1 / 5 - v2;
    std::cout << v1 << v2 << v3 << v1 * v2 << '\n';
    std::cout << b << b * v1;

    std::cout << linalg::cross({1, 0, 0}, {0, 1, 0});

    std::cout << linalg::matrix::id(3) *
                     linalg::matrix({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

    std::cout << linalg::matrix::id(5) << linalg::vector::zero(3);

    linalg::matrix s = {{1, 2, 4, 5}, {6, 2, 7, 4}, {1, 7, 8, 5}, {3, 8, 9, 8}};
    auto sinv = s.inv();
    double dets = s.det();
    std::cout << s << '\n';
    std::cout << sinv << '\n';
    std::cout << s * sinv << '\n';
    std::cout << dets << '\n';

    return 0;
}
