#pragma once

typedef unsigned int uint;

class NetworkData
{
    //NEXT: make a get next data funtion to be able to use huge amounts of data wihtout loading it into ram
    public:
        virtual void getNextData(long double*& inputs, long double*& outputs) = 0;
        virtual void getSameData(long double*& inputs, long double*& outputs) = 0;
};

