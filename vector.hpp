#pragma once

#include <iostream>

namespace linalg
{

template<int N>
class vector
{
private:
    float data[N];

public:
    const size_t n = N;

    vector() 
    {
        for(auto &i : data)
        {
            i = 0;
        }
    }

    vector(const vector<N>& other)
    {
        
    }

};
}
