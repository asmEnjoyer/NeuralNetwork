#include "MNISTData.h"
#include "Network.h"
#include "Log.h"


int main()
{
    NetworkData* data = new MNISTData();
    Network* network = new Network(data,0.1f,0.0f);
    Log.Level(Log.error|Log.info);
    network->train(50);

}

