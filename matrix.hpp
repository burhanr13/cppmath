#pragma once

#include "vector.hpp"
#include <iostream>

namespace linalg
{

template <size_t M, size_t N>
class matrix
{
private:
    vector<N> data[M];

    template <size_t K>
    double reduce(matrix<M, K> &right)
    {
        double det = 1;

        int i = 0;
        int j = 0;
        while (i < M && j < N)
        {
            int k = j;
            while (data[k][i] == 0)
            {
                k++;
                if (k >= M)
                {
                    i++;
                    k = j;
                    if (i >= N) return 0;
                }
            }
            std::swap(data[j], data[k]);
            if (K != 0) std::swap(right[j], right[k]);

            det *= data[j][i];
            if (K != 0) right[j] /= data[j][i];
            data[j] /= data[j][i];
            for (int p = 0; p < M; p++)
            {
                if (p == j) continue;
                
                if (K != 0) right[p] -= data[p][i] * right[j];
                data[p] -= data[p][i] * data[j];
            }

            i++;
            j++;
        }
        return det;
    }

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

    matrix(std::initializer_list<vector<N>> arr)
    {
        int i = 0;
        for (auto &row : arr)
        {
            data[i] = row;
            i++;
        }
    }

    matrix(const matrix<M, N> &o)
    {
        *this = o;
    }

    matrix<M, N> &operator=(const matrix<M, N> &o)
    {
        for (int i = 0; i < M; i++)
        {
            data[i] = o[i];
        }
        return *this;
    }

    bool operator==(const matrix<M, N> &o) const
    {
        for (int i = 0; i < M; i++)
        {
            if (data[i] != o[i]) return false;
        }
        return true;
    }

    bool operator!=(const matrix<M, N> &o) const
    {
        return !(*this == o);
    }

    vector<N> &
    operator[](int i)
    {
        return data[i];
    }

    const vector<N> &operator[](int i) const
    {
        return data[i];
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

    friend matrix<M, N> operator*(double s, matrix<M, N> &a)
    {
        return a * s;
    }

    matrix<M, N> &operator+=(const matrix<M, N> &b)
    {
        for (int i = 0; i < M; i++)
        {
            data[i] += b[i];
        }
        return *this;
    }

    matrix<M, N> &operator-=(const matrix<M, N> &b)
    {
        for (int i = 0; i < M; i++)
        {
            data[i] -= b[i];
        }
        return *this;
    }

    matrix<M, N> &operator*=(double s)
    {
        for (int i = 0; i < M; i++)
        {
            data[i] *= s;
        }
        return *this;
    }

    matrix<M, N> &operator/=(double s)
    {
        for (int i = 0; i < M; i++)
        {
            data[i] /= s;
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
            res[i] = data[i] * v;
        }
        return res;
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

    matrix<N, N> inv() const
    {
        if (M != N) return matrix<N, N>();
        matrix<N, N> inv(1);
        auto red = *this;
        red.reduce(inv);
        return inv;
    }

    double det() const
    {
        if (M != N) return 0;
        auto red = *this;
        auto dummy = matrix<N, 0>();
        return red.reduce(dummy);
    }

    friend std::ostream &
    operator<<(std::ostream &s, const matrix &a)
    {
        for (auto &i : a.data)
        {
            s << i;
        }
        return s;
    }

    template <size_t I, size_t J>
    friend class matrix;
};

} // namespace linalg
