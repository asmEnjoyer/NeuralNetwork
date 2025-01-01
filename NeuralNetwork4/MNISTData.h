#pragma once
#include "NetworkData.h"
#include <fstream>
#include <stdlib.h>
class MNISTData :
    public NetworkData
{
    private:
		//11 outputs for the 10 digits and noise
		int _networkLayout[6] = { 784,100,100,100,100,11 };
		int _numberOfLayers = 6;
		int _trainingSetCount = 60000;

		long double* _pTrainingInputArray;
		long double* _pTrainingOutputArray;
		long double* _pTestInputArray;
		long double* _pTestOutputArray;

		std::fstream _trainingInputs;
		std::fstream _trainingOutputs;
		std::fstream _testInputs;
		std::fstream _testOutputs;

    public:

		/// <summary>
		/// Create the data set for the MNIST problem.
		/// </summary>
		MNISTData();

		/// <summary>
		/// Free space allocated for arrays.
		/// </summary>
		~MNISTData();

		/// <summary>
		/// Get the next data from the data set.
		/// </summary>
		/// <param name="inputs">The inputs of the data</param>
		/// <param name="outputs">The outputs of the data</param>
        void getNextTrainingData(long double*& inputs, long double*& outputs) override;

		/// <summary>
		/// Get the same data from the data set.
		/// </summary>
		/// <param name="inputs">The inputs of the data</param>
		/// <param name="outputs">The outputs of the data</param>
        void getSameTrainingData(long double*& inputs, long double*& outputs) override;

		/// <summary>
		/// Get the next test data from the data set.
		/// </summary>
		/// <param name="inputs">The inputs of the data</param>
		/// <param name="outputs">The outputs of the data</param>
		bool getNextTestData(long double*& inputs, long double*& outputs) override;

		/// <summary>
		/// Get the same test data from the data set.
		/// </summary>
		/// <param name="inputs">The inputs of the data</param>
		/// <param name="outputs">The outputs of the data</param>
		void getSameTestData(long double*& inputs, long double*& outputs) override;

		/// <summary>
		/// Reload the files.
		/// </summary>
		void reloadTrainingFiles();

		/// <summary>
		/// Load the test data.
		/// </summary>
		void loadTestData() override;

		/// <summary>
		/// Preprocess the data.
		/// </summary>
		/// <returns>the network layout as an array of integers</returns>
		int* getNetworkLayout() override;

		/// <summary>
		/// Get the number of layers in the network.
		/// </summary>
		/// <returns>the number of layers in the network</returns>
		int getNumberOfLayers() override;
};

