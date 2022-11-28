#include "matrix.hpp"
#include <iostream>

int main()
{

    linalg::matrix<3, 4> a = {{1, 2, 4, 5}, {3, 4, 6, 4}, {2, 6, 7, 8}};
    // for (int i = 0; i < 3;i++){
    //     for (int j = 0; j < 4;j++){
    //         a[i][j] = i * 4 + j;
    //     }
    // }

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
    std::cout << a.T();

    return 0;
}