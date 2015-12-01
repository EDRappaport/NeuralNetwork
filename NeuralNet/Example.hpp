#ifndef _EXAMPLE_H
#define _EXAMPLE_H

#include <iostream>
#include <fstream>
#include <vector>

class Example
{
public:
    Example(std::vector<double> inputs, std::vector<bool> outputs);
    
    std::vector<double> GetInputs();
    std::vector<bool> GetOutputs();
    
    int GetInputSize();
    int GetOutputSize();
    
private:   
    std::vector<double> _inputs;
    std::vector<bool> _expectedOutputs;
};


#endif