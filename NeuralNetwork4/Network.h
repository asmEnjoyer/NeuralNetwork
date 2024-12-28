#pragma once
#include "Layer.h"
#include "NetworkData.h"
#include "Log.h"
#include "assert.h"


class Network
{
	private:
		long double _lr;
		long double _error;
		int _inputs;
		int _outputs;
		int _cLayers;
		Layer** _ppLayers;
		NetworkData* _data;

		int _precission;
		bool _count;

	public:

		/// <summary>
		/// Create a network with the given data and learning rate.
		/// </summary>
		/// <param name="data">The data the network will be trained on</param>
		/// <param name="lr">The learning rate of the network</param>
		Network(NetworkData* data,long double lr);

		/// <summary>
		/// Free space allocated for arrays.
		/// </summary>
		~Network();

		/// <summary>
		/// Train the network for the given number of epochs.
		/// </summary>
		/// <param name="epochs">The number of epochs the network will be trained for</param>
		void train(int epochs);

		/// <summary>
		/// Calculate the error of the network.
		/// </summary>
		/// <param name="expectedOutputs">The expected outputs of the network</param>
		/// <param name="calculatedOutputs">The calculated outputs of the network</param>
		/// <param name="outputCount">The number of outputs</param>
		/// <returns>The error of the network</returns>
		static long double calculateError(long double* expectedOutputs, long double* calculatedOutputs, int outputCount);
	private:

		/// <summary>
		/// Train the network for one epoch.
		/// </summary>
		void train();

		/// <summary>
		/// Calculate the outputs of the network based on the inputs.
		/// </summary>
		/// <param name="inputs">The inputs of the network</param>
		/// <returns>The error of the network</returns>
		long double* compute(long double* inputs);

		void backpropagation(long double* inputs, long double* outputs);
};

