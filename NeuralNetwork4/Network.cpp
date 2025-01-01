#include "Network.h"

//NEXT: use memcpy to compy more data at once
//TODO: add a function to save the network to a file
//TODO: move most of the calculations onto the GPU

Network::Network(NetworkData* data,long double lr,long double wd)
{
	_lr = lr;
	_wd = wd;
	int layers = data->getNumberOfLayers();
	int* layout = data->getNetworkLayout();
	_ppLayers = new Layer*[layers-1];
	for (int i = 0; i < layers-2; i++)
	{
		_ppLayers[i] = new Layer(layout[i],layout[i+1],Layer::Type::hidden);
	}
	_ppLayers[layers - 2] = new Layer(layout[layers - 2], layout[layers - 1], Layer::Type::classification);
	_inputs = layout[0];
	_outputs = layout[layers - 1];
	_cLayers = layers-1;
	_data = data;
	_precission = 0;
	_count = false;
	srand((int)time(NULL));
}

Network::~Network()
{
	for (int i = 0; i < _cLayers; i++)
	{
		delete _ppLayers[i];
	}
	delete[] _ppLayers;
	_ppLayers = nullptr;
}

void Network::train(int epochs)
{
	for (int epoch = 0; epoch < epochs; epoch++)
	{
		_precission = testNetwork();
		Log(std::to_string(_precission) + " " + std::to_string(_lr));
		if (_precission/_lr < 0.5)
			_lr *= 0.5;
		for(int i=0;i<60000;i++)
			train();
	}

}

long double Network::calculateError(long double* expectedOutputs, long double* calculatedOutputs, int outputCount)
{
	long double finalError = 0;
	long double currentError;
	for (int i = 0; i < outputCount; i++)
	{
		currentError = expectedOutputs[i] - calculatedOutputs[i];
		currentError *= currentError;
		finalError += currentError;
	}
	return finalError;
}

void Network::train()
{
		long double* inputs;
		long double* outputs;
		long double* initInputs;
		_data->getNextTrainingData(inputs, outputs);
		initInputs = inputs;
		inputs = compute(inputs);
		backpropagation(inputs, outputs);

		delete[] initInputs;
		initInputs = nullptr;

}

long double* Network::compute(long double* inputs)
{
	for (int j = 0; j < _cLayers; j++)
	{
		inputs = _ppLayers[j]->Compute(inputs);
	}
	return inputs;

}

long double Network::testNetwork()
{
	long double* inputs;
	long double* outputs;
	_data->loadTestData();
	long double error = 0;
	int i = 0;
	while (_data->getNextTestData(inputs,outputs))
	{
		if (calculateError(compute(inputs), outputs, 11) >= 1)
			error++;
		i++;
		delete[] inputs;
		delete[] outputs;
	}
	return error / i;
}

void Network::backpropagation(long double* inputs, long double* outputs)
{
	outputs = _ppLayers[_cLayers - 1]->delta(outputs, Layer::DeltaMode::diffrence);
	for (int j = _cLayers - 2; j >= 0; j--)
	{
		outputs = _ppLayers[j]->delta(outputs, Layer::DeltaMode::multiplication);
	}

	for (int j = _cLayers - 1; j >= 1; j--)
	{
		_ppLayers[j]->descent(_ppLayers[j - 1]->_pOutputs, _lr,_wd);
	}
	delete[] outputs;
	_data->getSameTrainingData(inputs, outputs);
	_ppLayers[0]->descent(inputs, _lr,_wd);
	delete[] inputs;
	delete[] outputs;
}