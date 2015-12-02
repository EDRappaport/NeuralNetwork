#include <iostream>

#include "ExampleContainer.hpp"
#include "Example.hpp"

ExampleContainer::ExampleContainer(std::fstream* examplesFileStream)
{
    (*examplesFileStream) >> _numTrainingExamples >> _inputSize >> _outputSize;
    if (!(*examplesFileStream))
    {
	std::cerr <<"Invalid file format, try again!";
	exit(-1);
    }
    
    for (int i = 0; i < _numTrainingExamples; i++)
    {
	std::vector<double> inputs (_inputSize);
	std::vector<bool> outputs; outputs.reserve(_outputSize);

	for (int j = 0; j < _inputSize; j++)
	{
	    (*examplesFileStream) >> inputs[j];
	    if (!(*examplesFileStream))
	    {
		std::cerr <<"Invalid file format, try again!";
		exit(-1);
	    }
	}
	
	for (int j = 0; j < _outputSize; j++)
	{
	    bool nextOutput;
	    (*examplesFileStream) >> nextOutput;
	    if (!(*examplesFileStream))
	    {
		std::cerr <<"Invalid file format, try again!";
		exit(-1);
	    }
	    outputs.push_back(nextOutput);
	}

	_examples.push_back(Example(inputs, outputs));
    }
}

std::list< Example > ExampleContainer::GetExamples()
{
    return _examples;
}
