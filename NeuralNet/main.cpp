#include <iostream>
#include <fstream>
#include <list>

#include "ThreeLayerNetwork.hpp"
#include "Example.hpp"
#include "ExampleContainer.hpp"


int GetDoubleInput()
{
    double input;
    while(true)
    {
	std::cin >> input;
	if (!std::cin)
	{
	    //non-integer
	    std::cin.clear();
	    while (std::cin.get() != '\n'); // clear
	}
	else
	{
	    return input;
	}
	std::cout << "Please enter a legal entry!" << std::endl;
    }
}

int GetPositiveIntegerInput()
{
    int input;
    while(true)
    {
	std::cin >> input;
	if (!std::cin)
	{
	    //non-integer
	    std::cin.clear();
	    while (std::cin.get() != '\n'); // clear
	}
	else
	{
	    if (input > 0)
	    {
		return input;
	    }
	}
	std::cout << "Please enter a legal entry!" << std::endl;
    }
}

std::ifstream* GetFileOpen(std::string filename)
{
    while (true)
    {
	//std::string filename = "/home/elli/Documents/Dropbox/The Cooper Union/ArtificialIntelligence/NeuralNetworks/NeuralNet/sample.NNWDBC.init";// ;
	//std::cin >> filename;
	std::ifstream* fileStream = new std::ifstream();
	fileStream->open(filename.c_str());
	if (fileStream->is_open())
	{
	    return fileStream;
	}
	std::cout << "Unable to open file '" << filename << "' - please enter a filename of an openable file:" << std::endl;
    }
}

ThreeLayerNetwork LoadInitialNetwork()
{
    std::cout << "Please enter the filename for the initial network file:" << std::endl;
    std::ifstream* initNetwork = GetFileOpen("/home/elli/Documents/Dropbox/The Cooper Union/ArtificialIntelligence/NeuralNetworks/NeuralNet/sample.NNWDBC.init");
    ThreeLayerNetwork initialNetwork = ThreeLayerNetwork(initNetwork);
    initNetwork->close();
    return initialNetwork;
}

ExampleContainer LoadTrainingExamples()
{
    std::cout << "Please enter the filename for the training file:" << std::endl;
    std::ifstream* trainingFilestream = GetFileOpen("/home/elli/Documents/Dropbox/The Cooper Union/ArtificialIntelligence/NeuralNetworks/NeuralNet/wdbc.train");
    ExampleContainer examples = ExampleContainer(trainingFilestream);
    trainingFilestream->close();
    return examples;
}

int GetMaxNumberOfEpochs()
{
    std::cout << "Please enter an integer number of epochs for the training:" << std::endl;
    return 100; GetPositiveIntegerInput();
}

double GetLearningRate()
{
    std::cout << "Please enter a floating point number for the learning rate:" << std::endl;
    return .01; GetDoubleInput();
}

int main(int argc, char **argv)
{
    std::cout << "Hello, welcome to NeuralNetwork Training program!!" << std::endl;
    
    ThreeLayerNetwork initialNetwork = LoadInitialNetwork();
    ExampleContainer trainingExamples = LoadTrainingExamples();   
    int maxNumEpochs = GetMaxNumberOfEpochs();
    double learningRate = GetLearningRate();
}
