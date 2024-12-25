#include "Data.h"

Data::Data()
{

    _ppTrainingInputs = new long double* [_trainingSetCount];
    for (int i = 0; i < _trainingSetCount; i++)
    {
        _ppTrainingInputs[i] = new long double[_trainingInputCount];
    }

    //TODO: this should not be hardoded in the future
    _ppTrainingInputs[0][0] = 0.0f;  _ppTrainingInputs[0][1] = 0.0f;  _ppTrainingInputs[0][2] = 0.0f;
    _ppTrainingInputs[1][0] = 0.0f;  _ppTrainingInputs[1][1] = 0.0f;  _ppTrainingInputs[1][2] = 1.0f;
    _ppTrainingInputs[2][0] = 0.0f;  _ppTrainingInputs[2][1] = 1.0f;  _ppTrainingInputs[2][2] = 0.0f;
    _ppTrainingInputs[3][0] = 0.0f;  _ppTrainingInputs[3][1] = 1.0f;  _ppTrainingInputs[3][2] = 1.0f;
    _ppTrainingInputs[4][0] = 1.0f;  _ppTrainingInputs[4][1] = 0.0f;  _ppTrainingInputs[4][2] = 0.0f;
    _ppTrainingInputs[5][0] = 1.0f;  _ppTrainingInputs[5][1] = 0.0f;  _ppTrainingInputs[5][2] = 1.0f;
    _ppTrainingInputs[6][0] = 1.0f;  _ppTrainingInputs[6][1] = 1.0f;  _ppTrainingInputs[6][2] = 0.0f;
    _ppTrainingInputs[7][0] = 1.0f;  _ppTrainingInputs[7][1] = 1.0f;  _ppTrainingInputs[7][2] = 1.0f;

    _ppTrainingOutputs = new long double* [_trainingSetCount];
    for (int i = 0; i < _trainingSetCount; i++)
    {
        _ppTrainingOutputs[i] = new long double[_trainingOutputCount];
    }

    //TODO: this should not be hardoded in the future
    _ppTrainingOutputs[0][0] = 0.0f; _ppTrainingOutputs[0][1] = 0.0f;
    _ppTrainingOutputs[1][0] = 0.0f; _ppTrainingOutputs[1][1] = 1.0f;
    _ppTrainingOutputs[2][0] = 0.0f; _ppTrainingOutputs[2][1] = 1.0f;
    _ppTrainingOutputs[3][0] = 1.0f; _ppTrainingOutputs[3][1] = 0.0f;
    _ppTrainingOutputs[4][0] = 0.0f; _ppTrainingOutputs[4][1] = 1.0f;
    _ppTrainingOutputs[5][0] = 1.0f; _ppTrainingOutputs[5][1] = 0.0f;
    _ppTrainingOutputs[6][0] = 1.0f; _ppTrainingOutputs[6][1] = 0.0f;
    _ppTrainingOutputs[7][0] = 1.0f; _ppTrainingOutputs[7][1] = 1.0f;
}

Data::~Data()
{
    for (int i = 0; i < _trainingSetCount; i++)
    {
        delete[] _ppTrainingInputs[i];
        delete[] _ppTrainingOutputs[i];
    }

    delete[] _ppTrainingInputs;
    delete[] _ppTrainingOutputs;
}

void Data::getNextData(long double*& inputs, long double*& outputs)
{
    _i = (_i + 1) % _trainingSetCount;
    inputs = new long double[_trainingInputCount];
    outputs = new long double[_trainingOutputCount];
    for(int i=0;i<_trainingInputCount;i++)
        inputs[i]=_ppTrainingInputs[_i][i];
    for(int i=0;i<_trainingOutputCount;i++)
        outputs[i] = _ppTrainingOutputs[_i][i];
}

void Data::getSameData(long double*& inputs, long double*& outputs)
{
    inputs = new long double[_trainingInputCount];
    outputs = new long double[_trainingOutputCount];
    for (int i = 0;i < _trainingInputCount;i++)
        inputs[i] = _ppTrainingInputs[_i][i];
    for (int i = 0;i < _trainingOutputCount;i++)
        outputs[i] = _ppTrainingOutputs[_i][i];
}
