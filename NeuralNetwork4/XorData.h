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

    int numberOfLayers = 4;
    int NetworkLayout[4] = { 3,9,9,2 };


	public:
        XorData();
        ~XorData();

		void getNextData(long double*& inputs, long double*& outputs) override;
        void getSameData(long double*& inputs, long double*& outputs) override;
        int* getNetworkLayout();
        int getNumberOfLayers();



};

