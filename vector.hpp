#pragma once

#include "matrix.hpp"
#include <iostream>

namespace linalg
{

template <size_t M, size_t N>
class matrix;

template <size_t N>
class ref_vector;

template <size_t N>
class vector
{
private:
    double data[N];

public:
    const size_t n = N;

    vector()
    {
        for (auto &i : data)
        {
            i = 0;
        }
    }

    vector(std::initializer_list<double> l)
    {
        int i = 0;
        for (double a : l)
        {
            data[i] = a;
            i++;
        }
    }

    vector(const vector<N> &other) { (*this) = other; }

    vector(const ref_vector<N> &o)
    {
        for (int i = 0; i < N; i++)
        {
            data[i] = o[i];
        }
    }

    vector<N> &operator=(const vector<N> &o)
    {
        for (int i = 0; i < N; i++)
        {
            data[i] = o[i];
        }
        return *this;
    }

    double &operator[](int i) { return data[i]; }

    double operator[](int i) const { return data[i]; }

    vector<N> &operator+=(const vector<N> &o)
    {
        for (int i = 0; i < N; i++)
        {
            data[i] += o[i];
        }
        return *this;
    }

    vector<N> &operator-=(const vector<N> &o)
    {
        for (int i = 0; i < N; i++)
        {
            data[i] -= o[i];
        }
        return *this;
    }

    vector<N> &operator*=(double s)
    {
        for (int i = 0; i < N; i++)
        {
            data[i] *= s;
        }
        return *this;
    }

    vector<N> &operator/=(double s)
    {
        for (int i = 0; i < N; i++)
        {
            data[i] /= s;
        }
        return *this;
    }

    vector<N> operator+(const vector<N> &o) const
    {
        auto res = *this;
        res += o;
        return res;
    }

    vector<N> operator-(const vector<N> &o) const
    {
        auto res = *this;
        res -= o;
        return res;
    }

    vector<N> operator*(double s) const
    {
        auto res = *this;
        res *= s;
        return res;
    }

    friend vector<N> operator*(double s, const vector<N> &v)
    {
        return v * s;
    }

    vector<N> operator-() const
    {
        return -1 * *this;
    }

    vector<N> operator/(double s) const
    {
        auto res = *this;
        res /= s;
        return res;
    }

    double operator*(const vector<N> &o) const
    {
        double sum = 0;
        for (int i = 0; i < N; i++)
        {
            sum += data[i] * o[i];
        }
        return sum;
    }

    matrix<N, 1> to_col() const
    {
        matrix<N, 1> res;
        for (int i = 0; i < N; i++)
        {
            res[i][0] = data[i];
        }
        return res;
    }

    matrix<1, N> to_row() const
    {
        matrix<1, N> res;
        for (int i = 0; i < N; i++)
        {
            res[0][i] = data[i];
        }
        return res;
    }

    friend std::ostream &operator<<(std::ostream &s, const vector &v)
    {
        s << "[ ";
        for (int i = 0; i < N; i++)
        {
            s << v.data[i] << ' ';
        }
        s << "]\n";
        return s;
    }
};

vector<3> cross(const vector<3> &a, const vector<3> &b)
{
    return {a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2],
            a[0] * b[1] - a[1] * b[0]};
}

} // namespace linalg
