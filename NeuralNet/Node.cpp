#include <iostream>
#include <cmath>
#include <stdlib.h> 

#include "Node.hpp"

Node::Node(std::vector<double> weights)
{
    _weights = weights;
}

std::vector<double> Node::GetWeights()
{
    return _weights;
}

double Node::GetCurrentValue()
{
    return _currentValue;
}

double Node::GetError()
{
    return _errorValue;
}

void Node::SetFinalOutputError(bool expectedOutput)
{
    double expectedValue = expectedOutput ? 1 : 0;
    double delta = ActivationFunctionPrime(_inputValue)*(expectedValue-_currentValue);
    _errorValue = delta;
}

void Node::SetIntermediateError(double weightedOutputErrors)
{
    double delta = ActivationFunctionPrime(_inputValue)*weightedOutputErrors;
    _errorValue = delta;
}

void Node::SetValue(std::vector< double > inputs)
{
    if (inputs.size() != _weights.size() - 1)
    {
	std::cerr << "Input size and Node size do not match!!";
	exit(-1);
    }
    
    double newInput = -1*_weights[0];
    for (int i = 0; i < inputs.size(); i++)
    {
	newInput += inputs[i]*_weights[i+1];
    }
    
    _inputValue = newInput;
    _currentValue = ActivationFunction(newInput);
}

void Node::SetNewWeights(std::vector< double > inputs, double learningRate)
{
    _weights[0] += learningRate*-1*_errorValue;
    for (int i = 0; i < inputs.size(); i++)
    {
	_weights[i+1] += learningRate*inputs[i]*_errorValue;
    }
}

double Node::Sigmoid(double x)
{
    return 1.0 / (1.0 + exp(-x));
}


double Node::ActivationFunction(double input)
{
    return Sigmoid(input);
}

double Node::ActivationFunctionPrime(double input)
{
    return Sigmoid(input)*(1.0-Sigmoid(input));
}




