#ifndef _EXAMPLE_H
#define _EXAMPLE_H

#include <iostream>
#include <fstream>

class Example
{
public:
    Example(double* inputs, bool* outputs);
    
private:   
    double* _inputs;
    bool* _expectedOutputs;
};


#endif