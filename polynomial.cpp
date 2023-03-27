#include "polynomial.hpp"

#include "vector.hpp"
#include <cmath>
#include <initializer_list>
#include <iostream>

namespace algebra {

void polynomial::recalc_deg() {
    for (int i = v.n - 1; i >= 0; i++) {
        if (fabs(v[i]) > 1e-10) _deg = i;
    }
    _deg = -1;
}

polynomial::polynomial() : deg(_deg), _deg(-1) {}

polynomial::polynomial(std::initializer_list<double>& l) : deg(_deg), v(l) {
    recalc_deg();
}

polynomial::polynomial(const polynomial& o) : deg(_deg) {
    *this = o;
}

polynomial& polynomial::operator=(const polynomial& o) {
    _deg = o.deg;
    v = o.v;
    return *this;
}

bool polynomial::operator==(const polynomial& o) const {
    if (deg != o.deg) return false;
    return v == o.v;
}

bool polynomial::operator!=(const polynomial& o) const {
    return !(*this == o);
}

polynomial& polynomial::operator+=(const polynomial& o){
    v += o.v;
    recalc_deg();
}

double& polynomial::operator[](int i) {
    return v[i];
}

double polynomial::operator[](int i) const {
    return v[i];
}



double polynomial::operator()(double x) {
    double res = 0;
    for (int i = 0; i <= deg; i++) {
        res += v[i] * pow(x, i);
    }
    return res;
}

std::ostream& operator<<(std::ostream& s, polynomial& p) {
    for (int i = 0; i <= p.deg; i++) {
        s << p.v[i];
        if (i > 0) s << 'x';
        if (i > 1) s << '^' << i;
        if (i < p.deg) s << " + ";
    }
    return s;
}

} // namespace algebra
