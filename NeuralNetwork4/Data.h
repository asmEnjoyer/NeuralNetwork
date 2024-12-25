#pragma once
#include "NetworkData.h"
class Data : public NetworkData
{
private:
    uint _trainingSetCount = 8;
    uint _trainingInputCount = 3;
    uint _trainingOutputCount = 2;

    long double** _ppTrainingInputs;

    long double** _ppTrainingOutputs;


		int _i=0;
	public:
        Data();
        ~Data();

		void getNextData(long double*& inputs, long double*& outputs) override;
        void getSameData(long double*& inputs, long double*& outputs) override;


};

