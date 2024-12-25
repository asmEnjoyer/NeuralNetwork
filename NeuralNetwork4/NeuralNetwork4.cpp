#include "XorData.h"
#include "Utility.h"
#include "Network.h"
#include "Log.h"


int main()
{
    NetworkData* data = new XorData();
    int layout[] = {3,9,9,2};
    Network* network = new Network(layout, 4,data);
    Utility.lr = 0.1f;
    Log.Level(Log.error|Log.info);
    network->train(1000000000);

}

