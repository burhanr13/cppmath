#include <initializer_list>
#include <iostream>

#include "vector.hpp"

namespace algebra {

class polynomial {
private:
    linalg::vector v;
    int _deg;

    void recalc_deg();

public:
    const int& deg;

    polynomial();

    polynomial(std::initializer_list<double>& l);

    polynomial(double d);

    polynomial(const polynomial& o);

    polynomial& operator=(const polynomial& o);

    bool operator==(const polynomial& o) const;

    bool operator!=(const polynomial& o) const;

    double& operator[](int i);

    double operator[](int i) const;

    polynomial& operator+=(const polynomial& o);

    polynomial& operator-=(const polynomial& o);

    polynomial& operator*=(const polynomial& o);

    polynomial operator+(const polynomial& o) const;

    polynomial operator-(const polynomial& o) const;

    polynomial operator*(const polynomial& o) const;

    polynomial& operator*=(double d);

    polynomial& operator/=(double d);

    polynomial operator*(double d) const;

    friend polynomial operator*(double d, const polynomial& p);

    polynomial operator/(double d) const;

    polynomial operator-() const;

    polynomial operator()(const polynomial& o) const;

    double operator()(double x);

    friend std::ostream& operator<<(std::ostream& s, polynomial& p);
};

} // namespace algebra
