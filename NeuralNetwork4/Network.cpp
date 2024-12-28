#include "Network.h"

//NEXT: add and implement a function to test the network on data it has not seen before
//TODO: add a function to save the network to a file

//NEXT: split the train function into smaller functions


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
	_count = false;
	for (int epoch = 0; epoch < epochs; epoch++)
	{
		_precission = 0;
		for(int i=0;i<60000;i++)
			train();
		Log(std::to_string((long double)_precission/60000) + " " + std::to_string(_lr) + "\n");
		if (((long double)_precission / 60000)/_lr < 0.3)
			_lr *= 0.5;
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
		long double* initOutputs;
		_data->getNextData(inputs, outputs);
		initInputs = inputs;
		initOutputs = outputs;
		inputs = compute(inputs);
		
		/*if (compute(inputs, outputs)>=1)
		{
			_precission++;
		}*/

		//if (_error>=1)//||rand() % 100 == 0)
		//{
		//	if(_count)
		//		_precission++;
		//	else
		//		Log(std::to_string(outputs[0]) + " " + std::to_string(outputs[1]) + " " + std::to_string(outputs[2]) + " " + std::to_string(outputs[3]) + " " + std::to_string(outputs[4]) + " " + std::to_string(outputs[5]) + " " + std::to_string(outputs[6]) + " " + std::to_string(outputs[7]) + " " + std::to_string(outputs[8]) + " " + std::to_string(outputs[9]) + " " + std::to_string(outputs[10]) + "\t" + std::to_string(_lr)+"\n\t\t\t"+ std::to_string(inputs[0]) + " " + std::to_string(inputs[1]) + " " + std::to_string(inputs[2]) + " " + std::to_string(inputs[3]) + " " + std::to_string(inputs[4]) + " " + std::to_string(inputs[5]) + " " + std::to_string(inputs[6]) + " " + std::to_string(inputs[7]) + " " + std::to_string(inputs[8]) + " " + std::to_string(inputs[9]) + " " + std::to_string(inputs[10]) + "\t" + std::to_string(_lr) + "\n");
		//}

		backpropagation(inputs, outputs);

		delete[] initInputs;
		initInputs = nullptr;

		/*delete[] initOutputs;
		initOutputs = nullptr;*/

}

long double* Network::compute(long double* inputs)
{
	for (int j = 0; j < _cLayers; j++)
	{
		inputs = _ppLayers[j]->Compute(inputs);
	}
	return inputs;

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
		_ppLayers[j]->descent(_ppLayers[j - 1]->_pOutputs, _lr);
	}
	delete[] outputs;
	_data->getSameData(inputs, outputs);
	_ppLayers[0]->descent(inputs, _lr);
	delete[] inputs;
	delete[] outputs;
}