#include "MNISTData.h"

//NEXT continue working on this class

MNISTData::MNISTData()
{
	_inputs.open("MNISTData/train-images.idx3-ubyte", std::ios::in | std::ios::binary);
	_outputs.open("MNISTData/train-labels.idx1-ubyte", std::ios::in | std::ios::binary);
}

MNISTData::~MNISTData()
{
	_inputs.close();
	_outputs.close();
}

void MNISTData::getNextData(long double*& inputs, long double*& outputs)
{
	
}

void MNISTData::getSameData(long double*& inputs, long double*& outputs)
{

}

int* MNISTData::getNetworkLayout()
{
	return _networkLayout;
}

int MNISTData::getNumberOfLayers()
{
	return _numberOfLayers;
}
