#pragma once
#include "NetworkData.h"
#include <fstream>
class MNISTData :
    public NetworkData
{
    private:
		//11 outputs for the 10 digits and noise
		int _networkLayout[4] = { 784,28,28,11 };
		int _numberOfLayers = 4;
		int _trainingSetCount = 60000;

		std::fstream _inputs;
		std::fstream _outputs;

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
        void getNextData(long double*& inputs, long double*& outputs) override;

		/// <summary>
		/// Get the same data from the data set.
		/// </summary>
		/// <param name="inputs">The inputs of the data</param>
		/// <param name="outputs">The outputs of the data</param>
        void getSameData(long double*& inputs, long double*& outputs) override;

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

