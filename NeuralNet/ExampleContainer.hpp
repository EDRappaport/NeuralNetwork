#ifndef _EXAMPLECONTAINER_H
#define _EXAMPLECONTAINER_H

#include <list>
#include <fstream>

#include "Example.hpp"

class ExampleContainer
{
public:
    ExampleContainer(std::ifstream* examplesFileStream);
    
private:
    int _numTrainingExamples;
    int _inputSize;
    int _outputSize;
    
    std::list<Example> _examples;
};


#endif