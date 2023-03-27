#include "matrix.hpp"

#include "vector.hpp"
#include <iostream>

namespace linalg {

void matrix::reset_data(size_t m, size_t n) {
    delete[] data;
    _data_size = m;
    _vector_size = n;
    data = new vector[_data_size];
    for (int i = 0; i < _data_size; i++) {
        data[i].reset_data(_vector_size);
    }
}

double matrix::reduce(matrix& right, int& rank) {
    if (right.m != m) throw std::invalid_argument("columns must match");

    double det = 1;

    rank = 0;

    int i = 0;
    int j = 0;
    while (i < m && j < n) {
        int k = i;
        while (data[k][j] == 0) {
            k++;
            if (k >= m) {
                j++;
                k = i;
                if (j >= n) return 0;
            }
        }
        if(k!=i){
            std::swap(data[i], data[k]);
            if (right.n != 0) std::swap(right[i], right[k]);
        }

        det *= data[i][j];
        if (right.n != 0) right[i] /= data[i][j];
        data[i] /= data[i][j];
        for (int p = 0; p < m; p++) {
            if (p == i) continue;

            if (right.n != 0) right[p] -= data[p][j] * right[i];
            data[p] -= data[p][j] * data[i];
        }

        i++;
        j++;
        rank++;
    }
    return det;
}

matrix::matrix()
    : m(_data_size), n(_vector_size), _data_size(0), _vector_size(0),
      data(nullptr) {}

matrix::matrix(size_t m, size_t n)
    : m(_data_size), n(_vector_size), _data_size(m), _vector_size(n) {
    data = new vector[m];
    for (int i = 0; i < m; i++) {
        data[i].reset_data(n);
    }
}

matrix::~matrix() {
    delete[] data;
}

matrix::matrix(size_t m, size_t n, double x) : matrix(m, n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            data[i][j] = x;
        }
    }
}

matrix::matrix(std::initializer_list<vector> arr)
    : matrix(arr.size(), (*arr.begin()).n) {
    int i = 0;
    for (auto& row : arr) {
        data[i] = row;
        i++;
    }
}

matrix::matrix(const matrix& o) : matrix() {
    *this = o;
}

matrix& matrix::operator=(const matrix& o) {
    reset_data(o.m, o.n);
    for (int i = 0; i < m; i++) {
        data[i] = o[i];
    }
    return *this;
}

bool matrix::operator==(const matrix& o) const {
    if (o.m != m || o.n != n) return false;
    for (int i = 0; i < m; i++) {
        if (data[i] != o[i]) return false;
    }
    return true;
}

bool matrix::operator!=(const matrix& o) const {
    return !(*this == o);
}

vector& matrix::operator[](int i) {
    if (i < 0 || i >= m) throw std::out_of_range("invalid index");
    return data[i];
}

const vector& matrix::operator[](int i) const {
    if (i < 0 || i >= m) throw std::out_of_range("invalid index");
    return data[i];
}

matrix matrix::operator+(const matrix& b) const {
    matrix res = *this;
    return res += b;
}

matrix matrix::operator-(const matrix& b) const {
    matrix res = *this;
    return res -= b;
}

matrix matrix::operator*(double s) const {
    matrix res = *this;
    return res *= s;
}

matrix matrix::operator/(double s) const {
    matrix res = *this;
    return res /= s;
}

matrix operator*(double s, const matrix& a) {
    return a * s;
}

matrix& matrix::operator+=(const matrix& b) {
    for (int i = 0; i < std::min(m, b.m); i++) {
        data[i] += b[i];
    }
    return *this;
}

matrix& matrix::operator-=(const matrix& b) {
    for (int i = 0; i < std::min(m, b.m); i++) {
        data[i] -= b[i];
    }
    return *this;
}

matrix& matrix::operator*=(double s) {
    for (int i = 0; i < m; i++) {
        data[i] *= s;
    }
    return *this;
}

matrix& matrix::operator/=(double s) {
    for (int i = 0; i < m; i++) {
        data[i] /= s;
    }
    return *this;
}

matrix matrix::operator-() const {
    return -1 * *this;
}

matrix matrix::operator*(const matrix& b) const {
    if (n != b.m)
        throw std::invalid_argument(
            "wrong dimension for matrix multiplication");
    matrix res(m, b.n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < b.n; j++) {
            res.data[i][j] = 0;
            for (int k = 0; k < n; k++) {
                res.data[i][j] += data[i][k] * b.data[k][j];
            }
        }
    }
    return res;
}

vector matrix::operator*(const vector& v) const {
    vector res(m);
    for (int i = 0; i < m; i++) {
        res[i] = data[i] * v;
    }
    return res;
}

matrix matrix::T() const {
    matrix t(n, m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            t.data[j][i] = data[i][j];
        }
    }
    return t;
}

matrix matrix::inv() const {
    if (m != n) throw std::invalid_argument("cannot invert nonsquare matrix");
    matrix inv = id(n);
    auto red = *this;
    int rank;
    double det = red.reduce(inv, rank);
    if (det == 0) return zero(m, n);
    return inv;
}

double matrix::det() const {
    if (m != n) throw std::invalid_argument("cannot calculate determinant");
    auto red = *this;
    matrix tmp = matrix(n, 0);
    int rank;
    return red.reduce(tmp, rank);
}

int matrix::rank() const {
    auto red = *this;
    matrix tmp = matrix(n, 0);
    int rank;
    red.reduce(tmp, rank);
    return rank;
}

std::ostream& operator<<(std::ostream& s, const matrix& a) {
    s << "[\n";
    for (int i = 0; i < a.m; i++) {
        s << a.data[i];
    }
    s << "]\n";
    return s;
}

matrix matrix::id(size_t n) {
    matrix res = matrix(n, n, 0);
    for (int i = 0; i < n; i++) {
        res[i][i] = 1;
    }
    return res;
}

matrix matrix::zero(size_t m, size_t n) {
    return matrix(m, n, 0);
}

} // namespace linalg