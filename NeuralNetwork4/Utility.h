#pragma once


inline class utility
{
	public:
		long double lr;
		long double wd;
		long double error;

		utility();

		void fillWithNumberSequence(int* table,int size);
		void shuffle(int* array, int size);

		long double Random();

		long double CalculateError(long double* expectedOutputs, long double* calculatedOutputs, int outputCount);
}Utility;

