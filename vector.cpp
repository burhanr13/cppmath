#include "vector.hpp"

#include "matrix.hpp"
#include <iostream>

namespace linalg {

void vector::reset_data(size_t size) {
    _data_size = size;
    delete[] data;
    data = new double[size];
}

vector::vector() : _data_size(0), n(_data_size), data(nullptr) {}

vector::vector(size_t n) : n(_data_size), _data_size(n), data(new double[n]) {}

vector::~vector() {
    delete[] data;
}

vector::vector(size_t n, double x) : vector(n) {
    for (int i = 0; i < n; i++) {
        data[i] = x;
    }
}

vector::vector(std::initializer_list<double> l) : vector(l.size()) {
    int i = 0;
    for (double a : l) {
        data[i] = a;
        i++;
    }
}

vector::vector(const vector& other) : vector() {
    (*this) = other;
}

vector& vector::operator=(const vector& o) {
    reset_data(o.n);
    for (int i = 0; i < n; i++) {
        data[i] = o[i];
    }
    return *this;
}

bool vector::operator==(const vector& o) const {
    if (n != o.n) return false;
    for (int i = 0; i < n; i++) {
        if (data[i] != o.data[i]) return false;
    }
    return true;
}

bool vector::operator!=(const vector& o) const {
    return !(*this == o);
}

double& vector::operator[](int i) {
    if (i < 0 || i >= n) throw std::out_of_range("invalid index");
    return data[i];
}

double vector::operator[](int i) const {
    if (i < 0 || i >= n) throw std::out_of_range("invalid index");
    return data[i];
}

vector& vector::operator+=(const vector& o) {
    for (int i = 0; i < std::min(n, o.n); i++) {
        data[i] += o[i];
    }
    return *this;
}

vector& vector::operator-=(const vector& o) {
    for (int i = 0; i < std::min(n, o.n); i++) {
        data[i] -= o[i];
    }
    return *this;
}

vector& vector::operator*=(double s) {
    for (int i = 0; i < n; i++) {
        data[i] *= s;
    }
    return *this;
}

vector& vector::operator/=(double s) {
    for (int i = 0; i < n; i++) {
        data[i] /= s;
    }
    return *this;
}

vector vector::operator+(const vector& o) const {
    auto res = *this;
    res += o;
    return res;
}

vector vector::operator-(const vector& o) const {
    auto res = *this;
    res -= o;
    return res;
}

vector vector::operator*(double s) const {
    auto res = *this;
    res *= s;
    return res;
}

vector operator*(double s, const vector& v) {
    return v * s;
}

vector vector::operator-() const {
    return -1 * *this;
}

vector vector::operator/(double s) const {
    auto res = *this;
    res /= s;
    return res;
}

double vector::operator*(const vector& o) const {
    double sum = 0;
    for (int i = 0; i < std::min(n, o.n); i++) {
        sum += data[i] * o[i];
    }
    return sum;
}

matrix vector::to_col() const {
    matrix res(n, 1);
    for (int i = 0; i < n; i++) {
        res[i][0] = data[i];
    }
    return res;
}

matrix vector::to_row() const {
    matrix res(1, n);
    for (int i = 0; i < n; i++) {
        res[0][i] = data[i];
    }
    return res;
}

std::ostream& operator<<(std::ostream& s, const vector& v) {
    s << "[ ";
    for (int i = 0; i < v.n; i++) {
        s << v.data[i] << ' ';
    }
    s << "]\n";
    return s;
}

vector vector::zero(size_t n) {
    return vector(n, 0);
}

vector cross(const vector& a, const vector& b) {
    if (a.n != 3 || b.n != 3)
        throw std::invalid_argument("require 3 dimensional vectors");
    return {a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2],
            a[0] * b[1] - a[1] * b[0]};
}

} // namespace linalg
