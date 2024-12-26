#include "XorData.h"

XorData::XorData()
{

    _ppTrainingInputs = new long double* [_trainingSetCount];
    for (int i = 0; i < _trainingSetCount; i++)
    {
        _ppTrainingInputs[i] = new long double[_trainingInputCount];
    }

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

    _ppTrainingOutputs[0][0] = 0.25f; _ppTrainingOutputs[0][1] = 0.25f;
    _ppTrainingOutputs[1][0] = 0.25f; _ppTrainingOutputs[1][1] = 0.75f;
    _ppTrainingOutputs[2][0] = 0.25f; _ppTrainingOutputs[2][1] = 0.75f;
    _ppTrainingOutputs[3][0] = 0.75f; _ppTrainingOutputs[3][1] = 0.25f;
    _ppTrainingOutputs[4][0] = 0.25f; _ppTrainingOutputs[4][1] = 0.75f;
    _ppTrainingOutputs[5][0] = 0.75f; _ppTrainingOutputs[5][1] = 0.25f;
    _ppTrainingOutputs[6][0] = 0.75f; _ppTrainingOutputs[6][1] = 0.25f;
    _ppTrainingOutputs[7][0] = 0.75f; _ppTrainingOutputs[7][1] = 0.75f;

    preprocesData();
}

XorData::~XorData()
{
    for (int i = 0; i < _trainingSetCount; i++)
    {
        delete[] _ppTrainingInputs[i];
        delete[] _ppTrainingOutputs[i];
    }

    delete[] _ppTrainingInputs;
    delete[] _ppTrainingOutputs;
}

void XorData::getNextData(long double*& inputs, long double*& outputs)
{
    _i = (rand()) % _trainingSetCount;
    inputs = new long double[_trainingInputCount];
    outputs = new long double[_trainingOutputCount];
    for(int i=0;i<_trainingInputCount;i++)
        inputs[i]=_ppTrainingInputs[_i][i];
    for(int i=0;i<_trainingOutputCount;i++)
        outputs[i] = _ppTrainingOutputs[_i][i];
}

void XorData::getSameData(long double*& inputs, long double*& outputs)
{
    inputs = new long double[_trainingInputCount];
    outputs = new long double[_trainingOutputCount];
    for (int i = 0;i < _trainingInputCount;i++)
        inputs[i] = _ppTrainingInputs[_i][i];
    for (int i = 0;i < _trainingOutputCount;i++)
        outputs[i] = _ppTrainingOutputs[_i][i];
}

void XorData::calculateInputAverage()
{
    int n = 0;
    for (int i = 0;i < _trainingSetCount;i++)
    {
        for (int j = 0; j < _trainingInputCount; j++)
        {
            n++;
            _inputAverage += (_ppTrainingInputs[i][j] - _inputAverage) / n;
        }
    }
}

void XorData::calculateInputStandardDeviation()
{
    int n = 0;
    long double d;
    for (int i = 0;i < _trainingSetCount;i++)
    {
        for (int j = 0; j < _trainingInputCount; j++)
        {
            n++;
            d = _ppTrainingInputs[i][j] - _inputAverage;
            _inputStandardDeviation += d * d;
        }
    }
    // devide just by n becouse we have the whole population as the dataset
    _inputStandardDeviation /= n;
    _inputStandardDeviation = sqrt(_inputStandardDeviation);
}

void XorData::preprocesData()
{
    calculateInputAverage();
    calculateInputStandardDeviation();
    for (int i = 0;i < _trainingInputCount;i++)
    {
        for (int j = 0; j < _trainingInputCount; j++)
        {
            _ppTrainingInputs[i][j] = (_ppTrainingInputs[i][j] - _inputAverage) / _inputStandardDeviation;
        }
    }
}


int* XorData::getNetworkLayout() 
{
    return _networkLayout;
}

int XorData::getNumberOfLayers()
{
    return _numberOfLayers;
}
