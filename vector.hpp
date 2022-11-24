#pragma once


namespace linalg
{

template<int N>
class vector
{
private:
    float[N] data;

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
