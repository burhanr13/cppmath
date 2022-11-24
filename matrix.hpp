#pragma once

#include <iostream>
#include "vector.hpp"

namespace linalg
{

template <size_t N>
class ref_vector;

template <size_t M, size_t N>
class matrix
{
private:
    float data[M][N];
    ref_vector<N> rows[M];
    ref_vector<M> cols[N];

public:
    const size_t m = M;
    const size_t n = N;

    matrix()
    {

        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                cols[j].ptrs[i] = rows[i].ptrs[j] = &data[i][j];
                data[i][j] = 0;
            }
        }
    }

    matrix(const matrix<M, N> &o) : matrix()
    {
        *this = o;
    }

    matrix<M, N> &operator=(const matrix<M, N> &o)
    {
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                data[i][j] = o.data[i][j];
            }
        }
        return *this;
    }

    ref_vector<N> &operator[](int i)
    {
        return rows[i];
    }

    ref_vector<N> &row(int i)
    {
        return (*this)[i];
    }

    ref_vector<M> &col(int j)
    {
        if (j < 0 || j >= N)
            throw "index out of bounds";
        return cols[j];
    }

    const ref_vector<N> &operator[](int i) const
    {
        return rows[i];
    }

    const ref_vector<N> &row(int i) const
    {
        return (*this)[i];
    }

    const ref_vector<M> &col(int j) const
    {
        return cols[j];
    }

    matrix<M, N> operator+(const matrix<M, N> &b) const
    {
        matrix<M, N> res = *this;
        return res += b;
    }

    matrix<M, N> operator-(const matrix<M, N> &b) const
    {
        matrix<M, N> res = *this;
        return res -= b;
    }

    matrix<M, N> operator*(float s) const
    {
        matrix<M, N> res = *this;
        return res *= s;
    }

    matrix<M, N> operator/(float s) const
    {
        matrix<M, N> res = *this;
        return res /= s;
    }

    friend matrix<M, N> operator*(float s, matrix<M, N> a)
    {
        return a * s;
    }

    matrix<M, N> &operator+=(const matrix<M, N> &b)
    {
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                data[i][j] += b.data[i][j];
            }
        }
        return *this;
    }

    matrix<M, N> &operator-=(const matrix<M, N> &b)
    {
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                data[i][j] -= b.data[i][j];
            }
        }
        return *this;
    }

    matrix<M, N> &operator*=(float s)
    {
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                data[i][j] *= s;
            }
        }
        return *this;
    }

    matrix<M, N> &operator/=(float s)
    {
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                data[i][j] /= s;
            }
        }
        return *this;
    }

    matrix<M, N> operator-() const
    {
        return -1 * *this;
    }

    template <size_t K>
    matrix<M, K> operator*(const matrix<N, K> &b) const
    {
        matrix<M, K> res;
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < K; j++)
            {
                res[i][j] = row(i) * b.col(j);
            }
        }
        return res;
    }

    friend std::ostream &operator<<(std::ostream &s, matrix a)
    {
        for (int i = 0; i < M; i++)
        {
            s << "[ ";
            for (int j = 0; j < N; j++)
            {
                s << a.data[i][j] << ' ';
            }
            s << "]\n";
        }
        return s;
    }
};

template <size_t N>
class ref_vector
{
private:
    float *ptrs[N];

public:
    ref_vector<N> &operator+=(const ref_vector<N> &o)
    {
        for (int i = 0; i < N; i++)
        {
            *ptrs[i] += *o.ptrs[i];
        }
        return *this;
    }

    ref_vector<N> &operator-=(const ref_vector<N> &o)
    {
        for (int i = 0; i < N; i++)
        {
            *ptrs[i] -= *o.ptrs[i];
        }
        return *this;
    }

    ref_vector<N> &operator*=(float s)
    {
        for (int i = 0; i < N; i++)
        {
            *ptrs[i] *= s;
        }
        return *this;
    }

    ref_vector<N> &operator/=(float s)
    {
        for (int i = 0; i < N; i++)
        {
            *ptrs[i] /= s;
        }
        return *this;
    }

    float operator*(const ref_vector<N> &o) const
    {
        float sum = 0;
        for (int i = 0; i < N; i++)
        {
            sum += *ptrs[i] * *o.ptrs[i];
        }
        return sum;
    }

    float &operator[](int i)
    {
        return *ptrs[i];
    }

    float operator[](int i) const
    {
        return *ptrs[i];
    }

    template <size_t I, size_t J>
    friend class matrix;
};

}
