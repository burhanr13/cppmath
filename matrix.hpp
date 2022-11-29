#pragma once

#include "vector.hpp"
#include <iostream>

namespace linalg
{

template <size_t N>
class ref_vector;

template <size_t N>
class const_ref_vector;

template <size_t M, size_t N>
class matrix
{
private:
    double data[M][N];

public:
    const size_t m = M;
    const size_t n = N;

    matrix() {}

    matrix(double x)
    {
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (i == j)
                    data[i][j] = x;
                else
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
            }
            i++;
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

    bool operator==(const matrix<M, N> &o) const
    {
        for (int i = 0; i < M; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (data[i][j] != o.data[i][j]) return false;
            }
        }
        return true;
    }

    double &operator()(int i, int j)
    {
        return data[i][j];
    }

    double operator()(int i, int j) const
    {
        return data[i][j];
    }

    ref_vector<N> operator[](int i)
    {
        return row(i);
    }

    ref_vector<N> row(int i)
    {
        return ref_vector<N>(&(data[0][0]), i * N, 1);
    }

    ref_vector<M> col(int j)
    {
        return ref_vector<M>(&(data[0][0]), j, M);
    }

    const ref_vector<N> operator[](int i) const
    {
        return row(i);
    }

    const_ref_vector<N> row(int i) const
    {
        return const_ref_vector<N>(&(data[0][0]), i * N, 1);
    }

    const_ref_vector<M> col(int j) const
    {
        return const_ref_vector<M>(&(data[0][0]), j, M);
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
                res.data[i][j] = 0;
                for (int k = 0; k < N; k++)
                {
                    res.data[i][j] += data[i][k] * b.data[k][j];
                }
            }
        }
        return res;
    }

    vector<M> operator*(const vector<N> &v) const
    {
        vector<M> res;
        for (int i = 0; i < M; i++)
        {
            res[i] = 0;
            for (int j = 0; j < N; j++)
            {
                res[i] += data[i][j] * v[j];
            }
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
                t.data[j][i] = data[i][j];
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

    template <size_t I, size_t J>
    friend class matrix;
};

template <size_t N>
class ref_vector
{
private:
    double *const data;
    const size_t start;
    const size_t step;

public:
    ref_vector(double *const data, size_t start, size_t step) : data(data), start(start), step(step) {}

    ref_vector<N> &operator=(const ref_vector<N> &o)
    {
        for (int i = 0; i < N; i++)
        {
            (*this)[i] = o[i];
        }
        return *this;
    }

    ref_vector<N> &operator=(const vector<N> &o)
    {
        for (int i = 0; i < N; i++)
        {
            (*this)[i] = o[i];
        }
        return *this;
    }

    ref_vector<N> &operator+=(const ref_vector<N> &o)
    {
        for (int i = 0; i < N; i++)
        {
            (*this)[i] += o[i];
        }
        return *this;
    }

    ref_vector<N> &operator-=(const ref_vector<N> &o)
    {
        for (int i = 0; i < N; i++)
        {
            (*this)[i] -= o[i];
        }
        return *this;
    }

    ref_vector<N> &operator*=(double s)
    {
        for (int i = 0; i < N; i++)
        {
            (*this)[i] *= s;
        }
        return *this;
    }

    ref_vector<N> &operator/=(double s)
    {
        for (int i = 0; i < N; i++)
        {
            (*this)[i] /= s;
        }
        return *this;
    }

    double operator*(const ref_vector<N> &o) const
    {
        double sum = 0;
        for (int i = 0; i < N; i++)
        {
            sum += (*this)[i] * o[i];
        }
        return sum;
    }

    double &operator[](int i)
    {
        return *(data + start + (i * step));
    }

    double operator[](int i) const
    {
        return *(data + start + (i * step));
    }

    template <size_t I, size_t J>
    friend class matrix;
};

template <size_t N>
class const_ref_vector
{
private:
    const double *const data;
    const size_t start;
    const size_t step;

public:
    const_ref_vector(const double *data, size_t start, size_t step) : data(data), start(start), step(step) {}

    double operator[](int i) const
    {
        return *(data + start + (i * step));
    }
};

} // namespace linalg
