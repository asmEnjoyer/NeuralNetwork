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
		Layer(int inputs, int outputs, Type type);
		~Layer();
		void initWeights();
		long double Activation(long double x) const;
		long double dActivation(long double x) const;
		long double* Compute(long double* inputs);
		long double* Delta(long double* output, DeltaMode mode);
		void Descent(long double* inputs);

};

