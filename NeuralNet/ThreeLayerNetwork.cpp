#include <iostream>
#include <iomanip>

#include "ThreeLayerNetwork.hpp"
#include "InputHelper.hpp"
#include "Node.hpp"

ThreeLayerNetwork ThreeLayerNetwork::GetNewNetworkFromFile()
{
    std::cout << "Please enter the filename for the network file:" << std::endl;
    std::fstream* initNetwork = InputHelper::GetFileOpen("/home/elli/Documents/Dropbox/The Cooper Union/ArtificialIntelligence/NeuralNetworks/NeuralNet/sample.NNGrades.init", Read); //sample.NNGrades.05.100.trained");// 
    ThreeLayerNetwork initialNetwork = ThreeLayerNetwork(initNetwork);
    initNetwork->close();
    return initialNetwork;
}


ThreeLayerNetwork::ThreeLayerNetwork(std::fstream* const initialSetupFile)
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
	weightedOutputErrors += _outputNodes[i].GetWeights()[hiddenNodeNumber+1]*_outputNodes[i].GetError();
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

std::vector< bool > ThreeLayerNetwork::GetOutputs()
{
    std::vector<bool> outputs;
    for (int i = 0; i < _outputNodes.size(); i++)
    {
	outputs.push_back(_outputNodes[i].GetCurrentValue() > 0.5);
    }
    return outputs;
}


void ThreeLayerNetwork::OutputNetwork(std::fstream* outputFilestream)
{
    std::cout << _numInputNodes << " " << _numHiddenNodes << " " << _numOutputNodes << std::endl;    
    (*outputFilestream) << _numInputNodes << " " << _numHiddenNodes << " " << _numOutputNodes << std::endl;
    
    (*outputFilestream).setf(std::ios::fixed);
    (*outputFilestream) << std::setprecision(3);
    for (int i = 0; i < _hiddenNodes.size(); i++)
    {
	std::vector<double> weights = _hiddenNodes[i].GetWeights();
	for (int j = 0; j < weights.size(); j++)
	{
	    std::cout << " " << weights[j] << " ";
	    (*outputFilestream) << weights[j];
	    if (j != weights.size()-1) (*outputFilestream) << " ";
	}
	std::cout << std::endl;
	(*outputFilestream) << std::endl;
    }
    for (int i = 0; i < _outputNodes.size(); i++)
    {
	std::vector<double> weights = _outputNodes[i].GetWeights();
	for (int j = 0; j < weights.size(); j++)
	{
	    std::cout << " " << weights[j] << " ";
	    (*outputFilestream) << weights[j];
	    if (j != weights.size()-1) (*outputFilestream) << " ";
	}
	std::cout << std::endl;
	(*outputFilestream) << std::endl;
    }
}