#include "ThreeLayerNetwork.hpp"

ThreeLayerNetwork::ThreeLayerNetwork(std::ifstream* const initialSetupFile)
{
    (*initialSetupFile) >> _numInputNodes >> _numHiddenNodes >> _numOutputNodes;
    if (!(*initialSetupFile))
    {
	std::cerr <<"Invalid file format, try again!";
	exit(-1);
    }
    
    _weights1 = new double*[_numHiddenNodes];
    for(int i = 0; i < _numHiddenNodes; i++)
    {
	_weights1[i] = new double[_numInputNodes+1];
    }
    
    _weights2 = new double*[_numOutputNodes];
    for(int i = 0; i < _numOutputNodes; i++)
    {
	_weights2[i] = new double[_numHiddenNodes+1];
    }
    
    for(int i = 0; i < _numHiddenNodes; i++)
    {
	for (int j = 0; j < _numInputNodes+1; j++)
	{
	    (*initialSetupFile) >> _weights1[i][j];
	    if (!(*initialSetupFile))
	    {
		std::cerr <<"Invalid file format, try again!";
		exit(-1);
	    }
	}
    }
    
    for(int i = 0; i < _numOutputNodes; i++)
    {
	for (int j = 0; j < _numHiddenNodes+1; j++)
	{
	    (*initialSetupFile) >> _weights1[i][j];
	    if (!(*initialSetupFile))
	    {
		std::cerr <<"Invalid file format, try again!";
		exit(-1);
	    }
	}
    }
    
    std::cout << _numInputNodes << ", " << _numHiddenNodes << ", " << _numOutputNodes;
}
