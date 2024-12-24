#include "NetworkData.h"

NetworkData::NetworkData()
{

    ppTrainingInputs = new long double* [trainingSetCount];
    for (int i = 0; i < trainingSetCount; i++)
    {
        ppTrainingInputs[i] = new long double[trainingInputCount];
    }

    //TODO: this should not be hardoded in the future
    ppTrainingInputs[0][0] = 0.0f;  ppTrainingInputs[0][1] = 0.0f;  ppTrainingInputs[0][2] = 0.0f;
    ppTrainingInputs[1][0] = 0.0f;  ppTrainingInputs[1][1] = 0.0f;  ppTrainingInputs[1][2] = 1.0f;
    ppTrainingInputs[2][0] = 0.0f;  ppTrainingInputs[2][1] = 1.0f;  ppTrainingInputs[2][2] = 0.0f;
    ppTrainingInputs[3][0] = 0.0f;  ppTrainingInputs[3][1] = 1.0f;  ppTrainingInputs[3][2] = 1.0f;
    ppTrainingInputs[4][0] = 1.0f;  ppTrainingInputs[4][1] = 0.0f;  ppTrainingInputs[4][2] = 0.0f;
    ppTrainingInputs[5][0] = 1.0f;  ppTrainingInputs[5][1] = 0.0f;  ppTrainingInputs[5][2] = 1.0f;
    ppTrainingInputs[6][0] = 1.0f;  ppTrainingInputs[6][1] = 1.0f;  ppTrainingInputs[6][2] = 0.0f;
    ppTrainingInputs[7][0] = 1.0f;  ppTrainingInputs[7][1] = 1.0f;  ppTrainingInputs[7][2] = 1.0f;

    ppTrainingOutputs = new long double* [trainingSetCount];
    for (int i = 0; i < trainingSetCount; i++)
    {
        ppTrainingOutputs[i] = new long double[trainingOutputCount];
    }

    //TODO: this should not be hardoded in the future
    ppTrainingOutputs[0][0] = 0.0f; ppTrainingOutputs[0][1] = 0.0f;
    ppTrainingOutputs[1][0] = 0.0f; ppTrainingOutputs[1][1] = 1.0f;
    ppTrainingOutputs[2][0] = 0.0f; ppTrainingOutputs[2][1] = 1.0f;
    ppTrainingOutputs[3][0] = 1.0f; ppTrainingOutputs[3][1] = 0.0f;
    ppTrainingOutputs[4][0] = 0.0f; ppTrainingOutputs[4][1] = 1.0f;
    ppTrainingOutputs[5][0] = 1.0f; ppTrainingOutputs[5][1] = 0.0f;
    ppTrainingOutputs[6][0] = 1.0f; ppTrainingOutputs[6][1] = 0.0f;
    ppTrainingOutputs[7][0] = 1.0f; ppTrainingOutputs[7][1] = 1.0f;
}

NetworkData::~NetworkData()
{
    for (int i = 0; i < trainingSetCount; i++)
    {
        delete[] ppTrainingInputs[i];
        delete[] ppTrainingOutputs[i];
    }

    delete[] ppTrainingInputs;
    delete[] ppTrainingOutputs;
}
