#include "Network.h"

//TODO add saving and loading the network data to a file

Network::Network(NetworkData* data,long double lr)
{
	_lr = lr;
	_error = 0;
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
	srand((int)time(NULL));
}

Network::~Network()
{
	for (int i = 0; i < _cLayers; i++)
	{
		delete _ppLayers[i];
	}
	delete[] _ppLayers;
}

void Network::train(int epochs)
{

	for (int epoch = 0; epoch < epochs; epoch++)
	{
		_error = 0;
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
		_data->getNextData(inputs, outputs);
		long double* firstInputs = inputs;
		for (int j = 0; j < _cLayers; j++)
		{
			inputs = _ppLayers[j]->Compute(inputs);
		}
		delete[] firstInputs;

		_error += calculateError(inputs, outputs, _outputs);
		if (rand() % 100 == 0)
			Log(std::to_string(calculateError(inputs, outputs, _outputs)) + "\t" + std::to_string(_lr));
		outputs = _ppLayers[_cLayers - 1]->Delta(outputs, Layer::DeltaMode::diffrence);
		for (int j = _cLayers - 2; j >= 0; j--)
		{
			outputs = _ppLayers[j]->Delta(outputs, Layer::DeltaMode::multiplication);
		}

		for (int j = _cLayers - 1; j >= 1; j--)
		{
			_ppLayers[j]->Descent(_ppLayers[j - 1]->_pOutputs,_lr);
		}
		delete[] outputs;
		_data->getSameData(inputs, outputs);
		_ppLayers[0]->Descent(inputs,_lr);

		delete[] inputs;
		delete[] outputs;

}
