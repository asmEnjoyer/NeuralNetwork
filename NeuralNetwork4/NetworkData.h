#pragma once

typedef unsigned int uint;

class NetworkData
{
    public:
        virtual void getNextData(long double*& inputs, long double*& outputs) = 0;
        virtual void getSameData(long double*& inputs, long double*& outputs) = 0;
};

