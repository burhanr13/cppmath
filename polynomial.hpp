#include "vector.hpp"
#include <cmath>
#include <initializer_list>
#include <iostream>

namespace algebra {

class polynomial {
private:
    linalg::vector v;

public:
    polynomial() {}

    polynomial(std::initializer_list<double>& l) : v(l) {}

    double operator[](int i) {
        return v[i];
    }

    double operator()(double x) {
        double res = 0;
        for (int i = 0; i < n; i++) {
            res += v[i] * pow(x, i);
        }
        return res;
    }

    friend std::ostream& operator<<(std::ostream& s, polynomial<n>& p) {
        for (int i = 0; i < n; i++) {
            s << v[i];
            if (i > 0) s << 'x';
            if (i > 1) s << '^' << i;
            if (i < n - 1) s << " + ";
        }
        return s;
    }
};
} // namespace algebra
