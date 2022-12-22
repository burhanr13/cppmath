#include <iostream>
#include "vector.hpp"
#include <initializer_list>
#include <cmath>

namespace algebra 
{

template<size_t N>
class polynomial
{
private:
    vector<N> v;

public:
    polynomial()
    {

    }

    polynomial(std::initializer_list<double> &l) : v(l) {}
    
    double operator[](int i)
    {
        return v[i];
    }

    double operator()(double x)
    {
        double res = 0;
        for(int i=0;i<N;i++)
        {
            res += v[i] * pow(x, i);
        }
        return res;
    }

    

    friend std::ostream &operator<<(std::ostream &s, polynomial<N> &p)
    {
        for(int i=0;i<N;i++)
        {
            s << v[i];
            if (i>0) s << 'x';
            if (i>1) s << '^' << i;
            if (i<N-1) s << " + ";
        }
        return s;
    }

};
}
