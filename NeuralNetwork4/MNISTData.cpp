#include "MNISTData.h"

MNISTData::MNISTData()
{
	_trainingInputs.open("train-images.ubyte", std::ios::in | std::ios::binary);
	_trainingOutputs.open("train-labels.ubyte", std::ios::in | std::ios::binary);

	char* skip = new char[16];
	_trainingInputs.read(skip, 16);
	_trainingOutputs.read(skip, 8);
	delete[] skip;

	_pTrainingInputArray = new long double[784];
	_pTrainingOutputArray = new long double[11];
	_pTestInputArray = new long double[784];
	_pTestOutputArray = new long double[11];
}

MNISTData::~MNISTData()
{
	_trainingInputs.close();
	_trainingOutputs.close();

	delete[] _pTrainingInputArray;
	delete[] _pTrainingOutputArray;
}

void MNISTData::getNextTrainingData(long double*& inputs, long double*& outputs)
{

	if (_trainingInputs.eof() || _trainingOutputs.eof())
	{
		reloadTrainingFiles();
	}
	inputs = new long double[784];
	outputs = new long double[11];
	if (rand() % 15 == 0)
	{
		for (int i = 0; i < 784; i++)
		{
			inputs[i] = (long double)(rand() % 256) / 255.0;
			_pTrainingInputArray[i] = inputs[i];
		}
		for (int i = 0; i < 11; i++)
		{
			outputs[i] = 0;
			_pTrainingOutputArray[i] = outputs[i];
		}
		outputs[10] = 1;
		_pTrainingOutputArray[10] = 1;
	}
	else
	{
		char* byte = new char;
		for (int i = 0; i < 784; i++)
		{
			_trainingInputs.read(byte, 1);
			inputs[i] = (long double)((unsigned char)*byte+(rand()%50-25)) / 255.0;
			inputs[i] = ((inputs[i] < 0) ? 0 : inputs[i]);
			inputs[i] = ((inputs[i] > 1) ? 1 : inputs[i]);
			_pTrainingInputArray[i] = inputs[i];
		}
		for (int i = 0; i < 11; i++)
		{
			outputs[i] = 0;
			_pTrainingOutputArray[i] = outputs[i];
		}
		_trainingOutputs.read(byte, 1);
		outputs[(int)*byte] = 1;
		_pTrainingOutputArray[(int)*byte] = 1;
		delete byte;
	}

	
}

void MNISTData::getSameTrainingData(long double*& inputs, long double*& outputs)
{
	inputs = new long double[784];
	outputs = new long double[11];
	for (int i = 0; i < 784; i++)
	{
		inputs[i] = _pTrainingInputArray[i];
	}
	for (int i = 0; i < 11; i++)
	{
		outputs[i] = _pTrainingOutputArray[i];
	}
}

bool MNISTData::getNextTestData(long double*& inputs, long double*& outputs)
{
	if (_trainingInputs.eof() || _trainingOutputs.eof()||!_trainingInputs.good()||!_trainingOutputs.good())
	{
		return false;
	}
	inputs = new long double[784];
	outputs = new long double[11];
	if (rand() % 15 == 0)
	{
		for (int i = 0; i < 784; i++)
		{
			inputs[i] = (long double)(rand() % 256) / 255.0;
			_pTestInputArray[i] = inputs[i];
		}
		for (int i = 0; i < 11; i++)
		{
			outputs[i] = 0;
			_pTestOutputArray[i] = outputs[i];
		}
		outputs[10] = 1;
		_pTestOutputArray[10] = 1;
	}
	else
	{
		char* byte = new char;
		for (int i = 0; i < 784; i++)
		{
			_testInputs.read(byte, 1);
			inputs[i] = (long double)((unsigned char)*byte) / 255.0;
			_pTestInputArray[i] = inputs[i];
		}
		for (int i = 0; i < 11; i++)
		{
			outputs[i] = 0;
			_pTestOutputArray[i] = outputs[i];
		}
		_testOutputs.read(byte, 1);
		if (*byte < 0 || *byte>10)
			return false;
		outputs[(int)*byte] = 1;
		_pTestOutputArray[(int)*byte] = 1;
		delete byte;
	}
	return true;
}

void MNISTData::getSameTestData(long double*& inputs, long double*& outputs)
{
	inputs = new long double[784];
	outputs = new long double[11];
	for (int i = 0; i < 784; i++)
	{
		inputs[i] = _pTestInputArray[i];
	}
	for (int i = 0; i < 11; i++)
	{
		outputs[i] = _pTestOutputArray[i];
	}

}

void MNISTData::reloadTrainingFiles()
{
	_trainingInputs.close();
	_trainingOutputs.close();
	_trainingInputs.open("train-images.ubyte", std::ios::in | std::ios::binary);
	_trainingOutputs.open("train-labels.ubyte", std::ios::in | std::ios::binary);

	char* skip = new char[16];
	_trainingInputs.read(skip, 16);
	_trainingOutputs.read(skip, 8);
	delete[] skip;
}

void MNISTData::loadTestData()
{
	_testInputs.close();
	_testOutputs.close();
	_testInputs.open("test-images.ubyte", std::ios::in | std::ios::binary);
	_testOutputs.open("test-labels.ubyte", std::ios::in | std::ios::binary);
	char* skip = new char[16];
	_testInputs.read(skip, 16);
	_testOutputs.read(skip, 8);
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
