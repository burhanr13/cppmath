#pragma once

#include <iostream>

namespace linalg {

class vector;

class matrix {
private:
    size_t _data_size;
    size_t _vector_size;
    vector* data;

    void reset_data(size_t m, size_t n);

    double reduce(matrix& right);

public:
    const size_t& m;
    const size_t& n;

    matrix();

    matrix(size_t m, size_t n);

    ~matrix();

    matrix(size_t m, size_t n, double x);

    matrix(std::initializer_list<vector> arr);

    matrix(const matrix& o);

    matrix& operator=(const matrix& o);

    bool operator==(const matrix& o) const;

    bool operator!=(const matrix& o) const;

    vector& operator[](int i);

    const vector& operator[](int i) const;

    matrix operator+(const matrix& b) const;

    matrix operator-(const matrix& b) const;

    matrix operator*(double s) const;

    matrix operator/(double s) const;

    friend matrix operator*(double s, const matrix& a);

    matrix& operator+=(const matrix& b);

    matrix& operator-=(const matrix& b);

    matrix& operator*=(double s);

    matrix& operator/=(double s);

    matrix operator-() const;

    matrix operator*(const matrix& b) const;

    vector operator*(const vector& v) const;

    matrix T() const;

    matrix inv() const;

    double det() const;

    friend std::ostream& operator<<(std::ostream& s, const matrix& a);

    static matrix id(size_t n);

    static matrix zero(size_t m, size_t n);
};

} // namespace linalg
