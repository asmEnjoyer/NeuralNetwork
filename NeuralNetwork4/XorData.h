#pragma once
#include "NetworkData.h"
#include <stdlib.h>
#include <cmath>

class XorData : public NetworkData
{
private:
    int _trainingSetCount = 8;
    int _trainingInputCount = 3;
    int _trainingOutputCount = 2;

    long double** _ppTrainingInputs;

    long double** _ppTrainingOutputs;

    int _i=0;

    int _numberOfLayers = 4;
    int _networkLayout[4] = { 3,9,9,2 };

    long double _inputAverage;
    long double _inputStandardDeviation;


	public:

		/// <summary>
		/// Create the data set for the XOR problem.
		/// </summary>
        XorData();

		/// <summary>
		/// Free space allocated for arrays.
		/// </summary>
        ~XorData();


		/// <summary>
		/// Get the next data from the data set.
		/// </summary>
		/// <param name="inputs">The inputs of the data</param>
		/// <param name="outputs">The outputs of the data</param>
		void getNextData(long double*& inputs, long double*& outputs) override;

		/// <summary>
		/// Get the same data from the data set.
		/// </summary>
		/// <param name="inputs">The inputs of the data</param>
		/// <param name="outputs">The outputs of the data</param>
        void getSameData(long double*& inputs, long double*& outputs) override;

		/// <summary>
		/// Calculate the average of the inputs.
		/// </summary>
        void calculateInputAverage();

		/// <summary>
		/// Calculate the standard deviation of the inputs.
		/// </summary>
        void calculateInputStandardDeviation();

		/// <summary>
		/// Preprocess the data.
		/// </summary>
        void preprocesData();

		/// <summary>
		/// Get the network layout.
		/// </summary>
		/// <returns>the network layout as an array of integers</returns>
        int* getNetworkLayout() override;

		/// <summary>
		/// Get the number of layers in the network.
		/// </summary>
		/// <returns>the number of layers in the network</returns>
        int getNumberOfLayers() override;



};

