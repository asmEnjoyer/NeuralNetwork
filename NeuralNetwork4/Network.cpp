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
	_ppLayers = nullptr;
}

void Network::train(int epochs)
{
	_count = false;
	for (int epoch = 0; epoch < epochs; epoch++)
	{
		_precission = 60000;
		_error = 0;
		if(epoch>=2)
		{
			_count = true;
			_precission = 0;
		}
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
		_data->getNextData(inputs, outputs);
		long double* firstInputs = inputs;
		for (int j = 0; j < _cLayers; j++)
		{
			inputs = _ppLayers[j]->Compute(inputs);
		}
		delete[] firstInputs;
		firstInputs = nullptr;

		_error = calculateError(inputs, outputs, _outputs);
		if (_error>=1)//||rand() % 100 == 0)
			/*Log(std::to_string(calculateError(inputs, outputs, _outputs)) + "\t" + std::to_string(_lr));*/
		{
			if(_count)
				_precission++;
			else
				Log(std::to_string(outputs[0]) + " " + std::to_string(outputs[1]) + " " + std::to_string(outputs[2]) + " " + std::to_string(outputs[3]) + " " + std::to_string(outputs[4]) + " " + std::to_string(outputs[5]) + " " + std::to_string(outputs[6]) + " " + std::to_string(outputs[7]) + " " + std::to_string(outputs[8]) + " " + std::to_string(outputs[9]) + " " + std::to_string(outputs[10]) + "\t" + std::to_string(_lr)+"\n\t\t\t"+ std::to_string(inputs[0]) + " " + std::to_string(inputs[1]) + " " + std::to_string(inputs[2]) + " " + std::to_string(inputs[3]) + " " + std::to_string(inputs[4]) + " " + std::to_string(inputs[5]) + " " + std::to_string(inputs[6]) + " " + std::to_string(inputs[7]) + " " + std::to_string(inputs[8]) + " " + std::to_string(inputs[9]) + " " + std::to_string(inputs[10]) + "\t" + std::to_string(_lr) + "\n");
		}
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
		outputs = nullptr;
		_data->getSameData(inputs, outputs);
		_ppLayers[0]->Descent(inputs,_lr);

		delete[] inputs;
		inputs = nullptr;

		delete[] outputs;
		outputs = nullptr;

}
