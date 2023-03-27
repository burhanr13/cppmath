#pragma once

#include <iostream>

namespace linalg {

class vector;

class matrix {
private:
    size_t _data_size;
    size_t _vector_size;
    vector* data;

    void reset_data(size_t m, size_t n) {
        delete[] data;
        _data_size = m;
        _vector_size = n;
        data = new vector[_data_size];
        for (int i = 0; i < _data_size; i++) {
            data[i].reset_data(_vector_size);
        }
    }

    double reduce(matrix& right) {
        if (right.m != m) throw std::invalid_argument("columns must match");

        double det = 1;

        int i = 0;
        int j = 0;
        while (i < m && j < n) {
            int k = j;
            while (data[k][i] == 0) {
                k++;
                if (k >= m) {
                    i++;
                    k = j;
                    if (i >= n) return 0;
                }
            }
            std::swap(data[j], data[k]);
            if (right.n != 0) std::swap(right[j], right[k]);

            det *= data[j][i];
            if (right.n != 0) right[j] /= data[j][i];
            data[j] /= data[j][i];
            for (int p = 0; p < m; p++) {
                if (p == j) continue;

                if (right.n != 0) right[p] -= data[p][i] * right[j];
                data[p] -= data[p][i] * data[j];
            }

            i++;
            j++;
        }
        return det;
    }

public:
    const size_t& m;
    const size_t& n;

    matrix()
        : m(_data_size), n(_vector_size), _data_size(0), _vector_size(0),
          data(nullptr) {}

    matrix(size_t m, size_t n)
        : m(_data_size), n(_vector_size), _data_size(m), _vector_size(n) {
        data = new vector[m];
        for (int i = 0; i < m; i++) {
            data[i].reset_data(n);
        }
    }

    ~matrix() {
        delete[] data;
    }

    matrix(size_t m, size_t n, double x) : matrix(m, n) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                data[i][j] = x;
            }
        }
    }

    matrix(std::initializer_list<vector> arr)
        : matrix(arr.size(), (*arr.begin()).n) {
        int i = 0;
        for (auto& row : arr) {
            data[i] = row;
            i++;
        }
    }

    matrix(const matrix& o) : matrix() {
        *this = o;
    }

    matrix& operator=(const matrix& o) {
        reset_data(o.m, o.n);
        for (int i = 0; i < m; i++) {
            data[i] = o[i];
        }
        return *this;
    }

    bool operator==(const matrix& o) const {
        if (o.m != m || o.n != n) return false;
        for (int i = 0; i < m; i++) {
            if (data[i] != o[i]) return false;
        }
        return true;
    }

    bool operator!=(const matrix& o) const {
        return !(*this == o);
    }

    vector& operator[](int i) {
        if (i < 0 || i >= m) throw std::out_of_range("invalid index");
        return data[i];
    }

    const vector& operator[](int i) const {
        if (i < 0 || i >= m) throw std::out_of_range("invalid index");
        return data[i];
    }

    matrix operator+(const matrix& b) const {
        matrix res = *this;
        return res += b;
    }

    matrix operator-(const matrix& b) const {
        matrix res = *this;
        return res -= b;
    }

    matrix operator*(double s) const {
        matrix res = *this;
        return res *= s;
    }

    matrix operator/(double s) const {
        matrix res = *this;
        return res /= s;
    }

    friend matrix operator*(double s, const matrix& a) {
        return a * s;
    }

    matrix& operator+=(const matrix& b) {
        for (int i = 0; i < std::min(m, b.m); i++) {
            data[i] += b[i];
        }
        return *this;
    }

    matrix& operator-=(const matrix& b) {
        for (int i = 0; i < std::min(m, b.m); i++) {
            data[i] -= b[i];
        }
        return *this;
    }

    matrix& operator*=(double s) {
        for (int i = 0; i < m; i++) {
            data[i] *= s;
        }
        return *this;
    }

    matrix& operator/=(double s) {
        for (int i = 0; i < m; i++) {
            data[i] /= s;
        }
        return *this;
    }

    matrix operator-() const {
        return -1 * *this;
    }

    matrix operator*(const matrix& b) const {
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

    vector operator*(const vector& v) const {
        vector res(m);
        for (int i = 0; i < m; i++) {
            res[i] = data[i] * v;
        }
        return res;
    }

    matrix T() const {
        matrix t(n, m);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                t.data[j][i] = data[i][j];
            }
        }
        return t;
    }

    matrix inv() const {
        if (m != n)
            throw std::invalid_argument("cannot invert nonsquare matrix");
        matrix inv(n, n, 1);
        auto red = *this;
        red.reduce(inv);
        return inv;
    }

    double det() const {
        if (m != n) throw std::invalid_argument("cannot calculate determinant");
        auto red = *this;
        auto dummy = matrix(n, 0);
        return red.reduce(dummy);
    }

    friend std::ostream& operator<<(std::ostream& s, const matrix& a) {
        for (int i = 0; i < a.m; i++) {
            s << a.data[i];
        }
        return s;
    }

    static matrix id(size_t n) {
        matrix res = matrix(n, n, 0);
        for (int i = 0; i < n;i++){
            res[i][i] = 1;
        }
        return res;
    }

    static matrix zero(size_t m, size_t n){
        return matrix(m, n, 0);
    }
};

} // namespace linalg
