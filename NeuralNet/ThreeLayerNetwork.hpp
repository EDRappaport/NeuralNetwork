#ifndef _THREELAYERNETWORK_H
#define _THREELAYERNETWORK_H

#include <iostream>
#include <fstream>

#include "Node.hpp"
#include "Example.hpp"

class ThreeLayerNetwork
{
public:
    ThreeLayerNetwork(std::fstream* initialSetupFile);
    static ThreeLayerNetwork GetNewNetworkFromFile();
    
    void PropogateForward(Example example);
    void PropogateErrorsBackward(Example example);
    void UpdateWeights(Example example, double learningRate);
    
    std::vector<bool> GetOutputs();
    
    int GetNumInputNodes();
    int GetNumHiddenNodes();
    int GetNumOutputNodes();
    
    void OutputNetwork(std::fstream* outputFilestream);
    
private:
    int _numInputNodes;
    int _numHiddenNodes;
    int _numOutputNodes;
    
    std::vector<Node> _hiddenNodes;
    std::vector<Node> _outputNodes;
    
    void InitializeSizes();
    double SumOutputErrors(int hiddenNodeNumber);
};


#endif