#include <iostream>
#include <fstream>
#include <list>
#include <stdlib.h> 

#include "ThreeLayerNetwork.hpp"
#include "Example.hpp"
#include "ExampleContainer.hpp"
#include "InputHelper.hpp"

ExampleContainer LoadTrainingExamples()
{
    std::cout << "Please enter the filename for the training file:" << std::endl;
    std::fstream* trainingFilestream = InputHelper::GetFileOpen("/home/elli/Documents/Dropbox/The Cooper Union/ArtificialIntelligence/NeuralNetworks/NeuralNet/grades.train", Read);
    ExampleContainer examples = ExampleContainer(trainingFilestream);
    trainingFilestream->close();
    return examples;
}

std::fstream* GetOutputFile()
{
    std::cout << "Please enter the name of the desired output file:" << std::endl;
    return InputHelper::GetFileOpen("OUTPUT", Write);
}

int GetMaxNumberOfEpochs()
{
    std::cout << "Please enter an integer number of epochs for the training:" << std::endl;
    return InputHelper::GetPositiveIntegerInput();
}

double GetLearningRate()
{
    std::cout << "Please enter a floating point number for the learning rate:" << std::endl;
    return InputHelper::GetDoubleInput();
}

int main(int argc, char **argv)
{
    std::cout << "Hello, welcome to NeuralNetwork Training program!!" << std::endl;
    
    ThreeLayerNetwork initialNetwork = ThreeLayerNetwork::GetNewNetworkFromFile(); //LoadInitialNetwork();
    ExampleContainer trainingExamples = LoadTrainingExamples();
    std::fstream* outputFile = GetOutputFile();
    int maxNumEpochs = GetMaxNumberOfEpochs();
    double learningRate = GetLearningRate();
    
    std::list<Example> examples = trainingExamples.GetExamples();
    
    std::cout << "Learning";
    for (int i = 0; i < maxNumEpochs; i++)
    {
	std::cout << "... ";
	std::list<Example>::iterator ex;
	for (ex = examples.begin(); ex != examples.end(); ex++)
	{
	    initialNetwork.PropogateForward((*ex));
	    initialNetwork.PropogateErrorsBackward((*ex));
	    initialNetwork.UpdateWeights((*ex), learningRate);
	}
    }
    std::cout << std::endl;
    initialNetwork.OutputNetwork(outputFile);
}
