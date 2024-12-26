#pragma once
class Layer
{
	public:
		enum DeltaMode
		{
			diffrence,multiplication
		};

		enum Type
		{
			hidden,
			classification,
			regression
		};
		long double* _pOutputs;

	private:
		int _cInputs;
		int _cOutputs;
		long double* _pBiases;
		long double** _ppWeights;
		long double* _pDelta;

		Type _type;

	public:

		/// <summary>
		/// Set variables and fill weight array with random weights.
		/// </summary>
		/// <param name="inputs">number of layer inputs</param>
		/// <param name="outputs"> number of layer outputs</param>
		/// <param name="type">type of the layer (hidden/final classification/final regression)</param>
		Layer(int inputs, int outputs, Type type);

		/// <summary>
		/// Free space allocated for arrays.
		/// </summary>
		~Layer();

		/// <summary>
		/// Fill weight array with random weights.
		/// </summary>
		void initWeights();

		/// <summary>
		/// Activation function for the neurons of the layer.
		/// Acts like diffrent activation functions based on layer type.
		/// </summary>
		/// <param name="x">input for the function</param>
		/// <returns>value the funtion takes with the argument x</returns>
		long double Activation(long double x) const;

		/// <summary>
		/// Derivative of the activation function.
		/// </summary>
		/// <param name="x">input for the derivative</param>
		/// <returns>value the derivative takes with the argument x</returns>
		long double dActivation(long double x) const;

		/// <summary>
		/// Calculate the outputs of the layer based on the inputs, weights, biases and activation function.
		/// </summary>
		/// <param name="inputs">array of inputs</param>
		/// <returns>an array of layer outputs</returns>
		long double* Compute(long double* inputs);

		/// <summary>
		/// Calculates the delta values (errors) for a neural network layer during backpropagation
		/// </summary>
		/// <param name="output">an array of output values</param>
		/// <param name="mode">an enum value that determines the mode of delta calculation</param>
		/// <returns>an array containing the propagated errors for the previous layer</returns>
		long double* Delta(long double* output, DeltaMode mode);

		/// <summary>
		/// updates the weights according to previously calculated delta values
		/// </summary>
		/// <param name="inputs">inputs the layer got</param>
		/// <param name="lr">learning rate</param>
		void Descent(long double* inputs,long double lr);

		/// <summary>
		/// Get a random double.
		/// </summary>
		/// <returns>number from range 0...1</returns>
		long double Random();

};

