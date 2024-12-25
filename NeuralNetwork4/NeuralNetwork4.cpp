#include "XorData.h"
#include "Utility.h"
#include "Network.h"
#include "Log.h"


int main()
{
    NetworkData* data = new XorData();
    Network* network = new Network(data);
    Utility.lr = 0.1f;
    Log.Level(Log.error|Log.info);
    network->train(1000000000);

}

