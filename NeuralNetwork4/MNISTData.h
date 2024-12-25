#pragma once
#include "NetworkData.h"
class MNISTData :
    public NetworkData
{
    public:
        void getNextData(long double*& inputs, long double*& outputs);
        void getSameData(long double*& inputs, long double*& outputs);

};

