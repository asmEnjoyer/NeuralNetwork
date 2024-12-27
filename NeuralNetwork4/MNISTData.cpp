#include "MNISTData.h"

MNISTData::MNISTData()
{
	_inputs.open("train-images.ubyte", std::ios::in | std::ios::binary);
	_outputs.open("train-labels.ubyte", std::ios::in | std::ios::binary);

	char* skip = new char[16];
	_inputs.read(skip, 16);
	_outputs.read(skip, 8);
	_pInputs = new long double[784];
	_pOutputs = new long double[11];

	delete[] skip;
}

MNISTData::~MNISTData()
{
	_inputs.close();
	_outputs.close();

	delete[] _pInputs;
	delete[] _pOutputs;
}

void MNISTData::getNextData(long double*& inputs, long double*& outputs)
{

	if (_inputs.eof() || _outputs.eof())
	{
		reloadFiles();
	}
	inputs = new long double[784];
	outputs = new long double[11];
	if (rand() % 15 == 0)
	{
		for (int i = 0; i < 784; i++)
		{
			inputs[i] = (long double)(rand() % 256) / 255.0;
			_pInputs[i] = inputs[i];
		}
		for (int i = 0; i < 11; i++)
		{
			outputs[i] = 0;
			_pOutputs[i] = outputs[i];
		}
		outputs[10] = 1;
		_pOutputs[10] = 1;
	}
	else
	{
		char* byte = new char;
		for (int i = 0; i < 784; i++)
		{
			_inputs.read(byte, 1);
			inputs[i] = (long double)((unsigned char)*byte) / 255.0;
			_pInputs[i] = inputs[i];
		}
		for (int i = 0; i < 11; i++)
		{
			outputs[i] = 0;
			_pOutputs[i] = outputs[i];
		}
		_outputs.read(byte, 1);
		outputs[(int)*byte] = 1;
		_pOutputs[(int)*byte] = 1;
		delete byte;
	}

	
}

void MNISTData::getSameData(long double*& inputs, long double*& outputs)
{
	inputs = new long double[784];
	outputs = new long double[11];
	for (int i = 0; i < 784; i++)
	{
		inputs[i] = _pInputs[i];
	}
	for (int i = 0; i < 11; i++)
	{
		outputs[i] = _pOutputs[i];
	}
}

void MNISTData::reloadFiles()
{
	_inputs.close();
	_outputs.close();
	_inputs.open("train-images.ubyte", std::ios::in | std::ios::binary);
	_outputs.open("train-labels.ubyte", std::ios::in | std::ios::binary);

	char* skip = new char[16];
	_inputs.read(skip, 16);
	_outputs.read(skip, 8);
	delete[] skip;
}

int* MNISTData::getNetworkLayout()
{
	return _networkLayout;
}

int MNISTData::getNumberOfLayers()
{
	return _numberOfLayers;
}
