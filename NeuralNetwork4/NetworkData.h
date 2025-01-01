#pragma once

class NetworkData
{
    public:

        /// <summary>
		/// Get the next data from the data set.
        /// </summary>
		/// <param name="inputs">The inputs of the data</param>
		/// <param name="outputs">The outputs of the data</param>
        virtual void getNextTrainingData(long double*& inputs, long double*& outputs) = 0;

		/// <summary>
		/// Get the same data from the data set.
		/// </summary>
		/// <param name="inputs">The inputs of the data</param>
		/// <param name="outputs">The outputs of the data</param>
        virtual void getSameTrainingData(long double*& inputs, long double*& outputs) = 0;

		/// <summary>
		/// Get the next test data from the data set.
		/// </summary>
		/// <param name="inputs">The inputs of the data</param>
		/// <param name="outputs">The outputs of the data</param>
		virtual bool getNextTestData(long double*& inputs, long double*& outputs) = 0;

		/// <summary>
		/// Get the same test data from the data set.
		/// </summary>
		/// <param name="inputs">The inputs of the data</param>
		/// <param name="outputs">The outputs of the data</param>
		virtual void getSameTestData(long double*& inputs, long double*& outputs) = 0;
		
		/// <summary>
		/// Load the test data.
		/// </summary>
		virtual void loadTestData() = 0;

		/// <summary>
		/// Preprocess the data.
		/// </summary>
		/// <returns>the network layout as an array of integers</returns>
        virtual int* getNetworkLayout() = 0;

		/// <summary>
		/// Get the number of layers in the network.
		/// </summary>
		/// <returns>the number of layers in the network</returns>
        virtual int getNumberOfLayers() = 0;
};

