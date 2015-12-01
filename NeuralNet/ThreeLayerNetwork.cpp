#include <iostream>

#include "ThreeLayerNetwork.hpp"
#include "Node.hpp"


ThreeLayerNetwork::ThreeLayerNetwork(std::ifstream* const initialSetupFile)
{
    (*initialSetupFile) >> _numInputNodes >> _numHiddenNodes >> _numOutputNodes;
    if (!(*initialSetupFile))
    {
	std::cerr <<"Invalid file format, try again!";
	exit(-1);
    }
    
    InitializeSizes();
    
    for(int i = 0; i < _numHiddenNodes; i++)
    {
	std::vector<double> currentWeights(_numInputNodes+1);
	for (int j = 0; j < _numInputNodes+1; j++)
	{
	    (*initialSetupFile) >> currentWeights[j];
	    if (!(*initialSetupFile))
	    {
		std::cerr <<"Invalid file format, try again!";
		exit(-1);
	    }
	}
	_hiddenNodes.push_back(Node(currentWeights));
    }
    
    for(int i = 0; i < _numOutputNodes; i++)
    {
	std::vector<double> currentWeights(_numHiddenNodes+1);
	for (int j = 0; j < _numHiddenNodes+1; j++)
	{
	    (*initialSetupFile) >> currentWeights[j];
	    if (!(*initialSetupFile))
	    {
		std::cerr <<"Invalid file format, try again!";
		exit(-1);
	    }
	}
	_outputNodes.push_back(Node(currentWeights));
    }
    
    std::cout << _numInputNodes << ", " << _numHiddenNodes << ", " << _numOutputNodes;
}

void ThreeLayerNetwork::InitializeSizes()
{
    _hiddenNodes.reserve(_numHiddenNodes);
    _outputNodes.reserve(_numOutputNodes);
}

double ThreeLayerNetwork::SumOutputErrors(int hiddenNodeNumber)
{
    double weightedOutputErrors = 0;
    for (int i = 0; i < _outputNodes.size(); i++)
    {
	weightedOutputErrors += _outputNodes[i].GetWeights()[hiddenNodeNumber]*_outputNodes[i].GetError();
    }
    return weightedOutputErrors;
}

void ThreeLayerNetwork::PropogateErrorsBackward(Example example)
{
    for (int i = 0; i < _outputNodes.size(); i++)
    {
	_outputNodes[i].SetFinalOutputError(example.GetOutputs()[i]);
    }
    for (int i = 0; i < _hiddenNodes.size(); i++)
    {
	_hiddenNodes[i].SetIntermediateError(SumOutputErrors(i));
    }
}


void ThreeLayerNetwork::PropogateForward(Example example)
{
    if (example.GetInputSize() != _numInputNodes || example.GetOutputSize() != _numOutputNodes)
    {
	std::cerr << "Example size does not match network size!!";
	exit(-1);
    }
    
    std::vector<double> hiddenLevel;
    for (int i = 0; i < _hiddenNodes.size(); i++)
    {
	_hiddenNodes[i].SetValue(example.GetInputs());
	hiddenLevel.push_back(_hiddenNodes[i].GetCurrentValue());
    }
    for (int i = 0; i < _outputNodes.size(); i++)
    {
	_outputNodes[i].SetValue(hiddenLevel);
    }
}

void ThreeLayerNetwork::UpdateWeights(Example example, double learningRate)
{
    std::vector<double> hiddenLevel;
    for (int i = 0; i < _hiddenNodes.size(); i++)
    {
	_hiddenNodes[i].SetNewWeights(example.GetInputs(), learningRate);
	hiddenLevel.push_back(_hiddenNodes[i].GetCurrentValue());
    }
    for (int i = 0; i < _outputNodes.size(); i++)
    {
	_outputNodes[i].SetNewWeights(hiddenLevel, learningRate);
    }
}

void ThreeLayerNetwork::OutputNetwork()
{
    for (int i = 0; i < _hiddenNodes.size(); i++)
    {
	std::vector<double> weights = _hiddenNodes[i].GetWeights();
	for (int j = 0; j < weights.size(); j++)
	{
	    std::cout << " " << weights[j] << " ";
	}
	std::cout << std::endl;
    }
    for (int i = 0; i < _outputNodes.size(); i++)
    {
	std::vector<double> weights = _outputNodes[i].GetWeights();
	for (int j = 0; j < weights.size(); j++)
	{
	    std::cout << " " << weights[j] << " ";
	}
	std::cout << std::endl;
    }
}