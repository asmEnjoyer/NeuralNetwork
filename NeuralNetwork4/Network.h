#pragma once
#include "Layer.h"
#include "NetworkData.h"
#include "Utility.h"
#include "Log.h"
#include "assert.h"

class Network
{
	private:
		int _inputs;
		int _outputs;
		int _cLayers;
		Layer** _ppLayers;
		NetworkData* _data;

	public:
		Network(NetworkData* data);
		~Network();
		void train(int epochs);
	private:
		void train();
};

