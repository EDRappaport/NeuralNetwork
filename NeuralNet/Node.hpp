#ifndef _NODE_H
#define _NODE_H

#include <vector>

class Node
{
public:
    Node(std::vector<double> weight);
    
    std::vector<double> GetWeights();
    
    double GetCurrentValue();
    double GetError();
    
    void SetValue(std::vector<double> inputs);
    void SetFinalOutputError(bool expectedOutput);
    void SetIntermediateError(double weightedOutputErrors);
    void SetNewWeights(std::vector< double > inputs, double learningRate);
    
private:
    std::vector<double> _weights;
    double _inputValue;
    double _currentValue;
    double _errorValue;
    
    static double Sigmoid(double x);
    static double ActivationFunction(double input);
    static double ActivationFunctionPrime(double input);
};


#endif