#include "Network.h"



Network::Network(int* layout,int layers,NetworkData* data)
{
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
	//TODO: make a logging library to replace the "disp" commented lines
	bool show;	//disp
	int i;

	int* trainingSetOrder = new int[_data->trainingSetCount];
	Utility.fillWithNumberSequence(trainingSetOrder, _data->trainingSetCount);

	Utility.error = 1000;
	for (int epoch = 0; epoch < epochs; epoch++)
	{
		Utility.shuffle(trainingSetOrder, _data->trainingSetCount);	
		show = false;	//disp
		if ((epoch + 1) % 10000 == 0)	//disp
		{
			show = true;	//disp
		}
		if (Utility.error / (_data->trainingSetCount * Utility.lr) < 0.0001)
			Utility.lr *= 0.5;
		if (epoch == epochs - 1)	//disp
			show = true;	//disp
	
	
		Utility.error = 0;
		for (int x = 0; x < (int)_data->trainingSetCount; x++)
		{
			i = trainingSetOrder[x];
			train(show, i);
		}
	}
	delete[] trainingSetOrder;

}

void Network::train(bool& show,int& i)
{
		long double* inputs = new long double[_inputs];
		long double* outputs = new long double[_outputs];
		for (int j = 0; j < _inputs; j++)
		{
			inputs[j] = _data->ppTrainingInputs[i][j];
		}
		for (int j = 0; j < _cLayers; j++)
		{
			inputs = _ppLayers[j]->Compute(inputs);
		}

		delete[] outputs;
		outputs = new long double[_outputs];
		for (int j = 0; j < _outputs; j++)
		{
			outputs[j] = _data->ppTrainingOutputs[i][j];
		}
		Utility.error += Utility.CalculateError(inputs, outputs, _outputs);
		if (show)
			Log(std::to_string(Utility.CalculateError(inputs, outputs, _outputs)) + "\t" + std::to_string(Utility.lr));
		outputs = _ppLayers[_cLayers - 1]->Delta(outputs, Layer::DeltaMode::diffrence);
		for (int j = _cLayers - 2; j >= 0; j--)
		{
			outputs = _ppLayers[j]->Delta(outputs, Layer::DeltaMode::multiplication);
		}

		for (int j = _cLayers - 1; j >= 1; j--)
		{
			_ppLayers[j]->Descent(_ppLayers[j - 1]->_pOutputs);
		}

		for (int j = 0; j < _inputs; j++)
		{
			inputs[j] = _data->ppTrainingInputs[i][j];
		}
		_ppLayers[0]->Descent(inputs);

}
