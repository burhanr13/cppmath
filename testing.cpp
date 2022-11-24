#include <iostream>
#include "matrix.hpp"

int main(){

    linalg::matrix<3, 4> a;
    for (int i = 0; i < 3;i++){
        for (int j = 0; j < 4;j++){
            a[i][j] = i * 4 + j;
        }
    }

    linalg::matrix<4, 3> b;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            b[i][j] = i * 3 + j;
        }
    }

    std::cout << a << b;
    std::cout << a * b;
    std::cout << a + a;
    std::cout << 5 * a;
    a[0] += a[2];
    std::cout << a;

    return 0;
}