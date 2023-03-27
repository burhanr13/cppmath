#pragma once

#include <iostream>

namespace linalg {

class matrix;

class vector {

    friend class matrix;

private:
    size_t _data_size;
    double* data;

    void reset_data(size_t size);

public:
    const size_t& n;

    vector();

    vector(size_t n);

    ~vector();

    vector(size_t n, double x);

    vector(std::initializer_list<double> l);

    vector(const vector& other);

    vector& operator=(const vector& o);

    bool operator==(const vector& o) const;

    bool operator!=(const vector& o) const;

    double& operator[](int i);

    double operator[](int i) const;

    vector& operator+=(const vector& o);

    vector& operator-=(const vector& o);

    vector& operator*=(double s);

    vector& operator/=(double s);

    vector operator+(const vector& o) const;

    vector operator-(const vector& o) const;

    vector operator*(double s) const;

    friend vector operator*(double s, const vector& v);

    vector operator-() const;

    vector operator/(double s) const;

    double operator*(const vector& o) const;

    matrix to_col() const;

    matrix to_row() const;

    friend std::ostream& operator<<(std::ostream& s, const vector& v);

    static vector zero(size_t n);
};

vector cross(const vector& a, const vector& b);

} // namespace linalg
