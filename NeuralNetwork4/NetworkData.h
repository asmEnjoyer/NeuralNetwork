#pragma once

typedef unsigned int uint;

class NetworkData
{
	public:
        uint trainingSetCount = 8;
        uint trainingInputCount = 3;
        uint trainingOutputCount = 2;

        long double** ppTrainingInputs;

        long double** ppTrainingOutputs;

        
        //NEXT: make a get next data funtion to be able to use huge amounts of data wihtout loading it into ram
        NetworkData();

        ~NetworkData();
};

