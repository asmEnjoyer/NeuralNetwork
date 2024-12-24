#include "Utility.h"
#include <ctime>
#include <stdlib.h>

utility::utility():
	lr(0),
	error(0),
	wd(0)
{
	srand((int)time(NULL));
	rand();
}

void utility::fillWithNumberSequence(int* table,int size)
{
	for (int i = 0;i < size;i++)
	{
		table[i] = i;
	}
}


void utility::shuffle(int* array, int size)
{
	int k;
	int t;
	while (size > 1)
	{
		k = rand() % (size--);
		t = array[size];
		array[size] = array[k];
		array[k] = t;
	}
}

long double utility::Random()
{
	long double ran = rand();

	return ran / RAND_MAX;
}

long double utility::CalculateError(long double* expectedOutputs, long double* calculatedOutputs, int outputCount)
{

	long double finalError=0;
	long double currentError;
	for (int i = 0;i < outputCount;i++)
	{
		currentError = expectedOutputs[i] - calculatedOutputs[i];
		currentError *= currentError;
		finalError += currentError;
	}
	return finalError;
}

