#include "ExampleContainer.hpp"
#include "Example.hpp"

ExampleContainer::ExampleContainer(std::ifstream* examplesFileStream)
{
    (*examplesFileStream) >> _numTrainingExamples >> _inputSize >> _outputSize;
    if (!(*examplesFileStream))
    {
	std::cerr <<"Invalid file format, try again!";
	exit(-1);
    }
    
    for (int i = 0; i < _numTrainingExamples; i++)
    {
	double* inputs = new double[_inputSize];
	bool* outputs = new bool[_outputSize];
	
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
	    (*examplesFileStream) >> outputs[j];
	    if (!(*examplesFileStream))
	    {
		std::cerr <<"Invalid file format, try again!";
		exit(-1);
	    }
	}
	
	_examples.push_back(Example(inputs, outputs));
    }
}