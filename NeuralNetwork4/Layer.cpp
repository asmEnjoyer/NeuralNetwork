#include "Layer.h"
#include <cmath>

Layer::Layer(int inputs, int outputs, Type type)
{
	_cInputs = inputs;
	_cOutputs = outputs;
	_pOutputs = new long double[outputs];
	_pBiases = new long double[outputs];
	_ppWeights = new long double* [inputs];
	for (int i = 0; i < _cInputs; i++)
	{
		_ppWeights[i] = new long double[outputs];
	}
	_pDelta = new long double[outputs];
	_type = type;

	initWeights();
	return;
}

Layer::~Layer()
{
	for (int i = 0;i < _cInputs;i++)
	{
		delete[] _ppWeights[i];
	}
	delete[] _ppWeights;
	delete[] _pBiases;
	delete[] _pDelta;
}

void Layer::initWeights()
{
	for (int i = 0; i < _cInputs; i++)
	{
		for (int j = 0; j < _cOutputs; j++)
		{
			_ppWeights[i][j] = Random()*-1;
		}
	}
	for (int i = 0; i < _cOutputs; i++)
	{
		_pBiases[i] = 0;//Utility::Random();
	}
}

long double Layer::Activation(long double x) const
{
	if (_type == hidden)
		return ((x<0)?x/10:x);
	if (_type == regression)
		return x;
	if (_type == classification)
		return 1/(1+exp(-x));
	return 0;
}

long double Layer::dActivation(long double x) const
{
	if (_type == hidden)
		return ((x < 0) ? 0.1 : 1);
	if (_type == regression)
		return 1;
	if (_type == classification)
		return x * (1 - x);
	return 0;
}

long double* Layer::Compute(long double* inputs)
{
	long double activation;
	for (int i = 0;i < _cOutputs;i++)
	{
		activation = _pBiases[i];
		for (int j = 0; j < _cInputs; j++)
		{
			activation += inputs[j] * _ppWeights[j][i];
		}
		_pOutputs[i] = Activation(activation);
	}
	return _pOutputs;
}

long double* Layer::Delta(long double* output, DeltaMode mode)
{
	if (mode == diffrence)
	{
		for (int i = 0; i < _cOutputs; i++)
		{
			long double error = (output[i] - _pOutputs[i]);
			_pDelta[i] = error*dActivation(_pOutputs[i]);
		}
	}
	else
	{
		for (int i = 0; i < _cOutputs; i++)
		{
			_pDelta[i] = output[i] * dActivation(_pOutputs[i]);
		}
	}

	delete[] output;
	output = new long double[_cInputs];
	long double error;
	for (int i = 0; i < _cInputs; i++)
	{
		error = 0.0f;
		for (int j = 0; j < _cOutputs; j++)
		{
			error += _pDelta[j] * _ppWeights[i][j];
		}
		output[i] = error;
	}
	return output;
}

void Layer::Descent(long double* inputs,long double lr)
{
	for (int i = 0; i < _cOutputs; i++)
	{
		_pBiases[i] += _pDelta[i] * lr;
		//_pBiases[i] *= (1 - Utility.wd);
		for (int j = 0; j < _cInputs; j++)
		{
			_ppWeights[j][i] += inputs[j] * _pDelta[i] * lr;
			//_ppWeights[j][i] *= (1 - Utility.wd);
		}
	}
}

long double Layer::Random()
{
	return (long double)rand() / RAND_MAX;
}