#pragma once

#include "vector.hpp"
#include <iostream>

namespace linalg
{

template <size_t N>
class ref_vector;

template <size_t M, size_t N>
class matrix
{
private:
    double data[M][N];
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

    matrix(std::initializer_list<std::initializer_list<double>> arr) : matrix()
    {
        int i = 0;
        for (auto &row : arr)
        {
            int j = 0;
            for (double el : row)
            {
                data[i][j] = el;
                j++;
                if (j >= N) break;
            }
            i++;
            if (i >= M) break;
        }
    }

    matrix(const matrix<M, N> &o) : matrix() { *this = o; }

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

    matrix<M, N> operator*(double s) const
    {
        matrix<M, N> res = *this;
        return res *= s;
    }

    matrix<M, N> operator/(double s) const
    {
        matrix<M, N> res = *this;
        return res /= s;
    }

    friend matrix<M, N> operator*(double s, matrix<M, N> &a) { return a * s; }

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

    matrix<M, N> &operator*=(double s)
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

    matrix<M, N> &operator/=(double s)
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

    matrix<M, N> operator-() const { return -1 * *this; }

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

    vector<M> operator*(const vector<N> &v) const
    {
        vector<M> res;
        for (int i = 0; i < M; i++)
        {
            res[i] = vector<N>(row(i)) * v;
        }
        return res;
    }

    void swapRows(int a, int b)
    {
        for (int i = 0; i < N; i++)
        {
            std::swap(data[a][i], data[b][i]);
        }
    }

    void swapCols(int a, int b)
    {
        for (int j = 0; j < M; j++)
        {
            std::swap(data[j][a], data[j][b]);
        }
    }

    matrix<N, M> T() const
    {
        matrix<N, M> t;
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                t[j][i] = data[i][j];
            }
        }
        return t;
    }

    friend std::ostream &operator<<(std::ostream &s, const matrix &a)
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
    double *ptrs[N];

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

    ref_vector<N> &operator*=(double s)
    {
        for (int i = 0; i < N; i++)
        {
            *ptrs[i] *= s;
        }
        return *this;
    }

    ref_vector<N> &operator/=(double s)
    {
        for (int i = 0; i < N; i++)
        {
            *ptrs[i] /= s;
        }
        return *this;
    }

    double operator*(const ref_vector<N> &o) const
    {
        double sum = 0;
        for (int i = 0; i < N; i++)
        {
            sum += *ptrs[i] * *o.ptrs[i];
        }
        return sum;
    }

    double &operator[](int i)
    {
        return *ptrs[i];
    }

    double operator[](int i) const
    {
        return *ptrs[i];
    }

    template <size_t I, size_t J>
    friend class matrix;
};

} // namespace linalg
