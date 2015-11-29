#ifndef _THREELAYERNETWORK_H
#define _THREELAYERNETWORK_H

#include <iostream>
#include <fstream>

class ThreeLayerNetwork
{
public:
    ThreeLayerNetwork(std::ifstream* initialSetupFile);
    
    int GetNumInputNodes();
    int GetNumHiddenNodes();
    int GetNumOutputNodes();
    
private:
    int _numInputNodes;
    int _numHiddenNodes;
    int _numOutputNodes;
    
    double** _weights1;
    double** _weights2;
};


#endif