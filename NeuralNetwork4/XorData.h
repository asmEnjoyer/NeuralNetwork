#pragma once
#include "NetworkData.h"
class XorData : public NetworkData
{
private:
    int _trainingSetCount = 8;
    int _trainingInputCount = 3;
    int _trainingOutputCount = 2;

    long double** _ppTrainingInputs;

    long double** _ppTrainingOutputs;


    int _i=0;
	public:
        XorData();
        ~XorData();

		void getNextData(long double*& inputs, long double*& outputs) override;
        void getSameData(long double*& inputs, long double*& outputs) override;


};

