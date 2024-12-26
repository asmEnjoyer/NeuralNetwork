#pragma once

class NetworkData
{
    public:

        /// <summary>
		/// Get the next data from the data set.
        /// </summary>
		/// <param name="inputs">The inputs of the data</param>
		/// <param name="outputs">The outputs of the data</param>
        virtual void getNextData(long double*& inputs, long double*& outputs) = 0;

		/// <summary>
		/// Get the same data from the data set.
		/// </summary>
		/// <param name="inputs">The inputs of the data</param>
		/// <param name="outputs">The outputs of the data</param>
        virtual void getSameData(long double*& inputs, long double*& outputs) = 0;

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

