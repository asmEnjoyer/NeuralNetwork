#pragma once


inline class utility
{
	public:
		long double lr;
		long double wd;
		long double error;

		/// <summary>
		/// Setup variables and initate randomness based on time.
		/// </summary>
		utility();

		/// <summary>
		/// Fill an array with a number sequence 0...size-1.
		/// </summary>
		/// <param name="table">- table to put numbers in</param>
		/// <param name="size">- size of the table</param>
		void fillWithNumberSequence(int* table,int size);

		/// <summary>
		/// Shuffles an array randomly (used in this project for random bucket numbers).
		/// </summary>
		/// <param name="array">- array to shuffle</param>
		/// <param name="size">- size of the array</param>
		void shuffle(int* array, int size);


		/// <summary>
		/// Get a random double.
		/// </summary>
		/// <returns>number from range 0...1</returns>
		long double Random();

		/// <summary>
		/// Calculate square error of a neural network.
		/// </summary>
		/// <param name="expectedOutputs">- expected outputs from actual data</param>
		/// <param name="calculatedOutputs">- outputs calculated by the neural network</param>
		/// <param name="outputCount">- output array size</param>
		/// <returns>the calculated error</returns>
		long double CalculateError(long double* expectedOutputs, long double* calculatedOutputs, int outputCount);
}Utility;

