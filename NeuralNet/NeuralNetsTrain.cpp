#include <iostream>
#include <fstream>
#include <list>

#include "ThreeLayerNetwork.hpp"
#include "Example.hpp"
#include "ExampleContainer.hpp"


double GetDoubleInput()
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

enum FileOpenType {Read, Write};

std::fstream* GetFileOpen(std::string filename, FileOpenType fileOpenType)
{
    std::ios_base::openmode openMode = fileOpenType == Read ? std::ios::in : std::ios::out;
    while (true)
    {
	//std::string filename;// = "/home/elli/Documents/Dropbox/The Cooper Union/ArtificialIntelligence/NeuralNetworks/NeuralNet/sample.NNWDBC.init";// ;
	std::cin >> filename;
	std::fstream* fileStream = new std::fstream();
	fileStream->open(filename.c_str(), openMode);
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
    std::fstream* initNetwork = GetFileOpen("/home/elli/Documents/Dropbox/The Cooper Union/ArtificialIntelligence/NeuralNetworks/NeuralNet/sample.NNGrades.init", Read); //sample.NNGrades.05.100.trained");// 
    ThreeLayerNetwork initialNetwork = ThreeLayerNetwork(initNetwork);
    initNetwork->close();
    return initialNetwork;
}

ExampleContainer LoadTrainingExamples()
{
    std::cout << "Please enter the filename for the training file:" << std::endl;
    std::fstream* trainingFilestream = GetFileOpen("/home/elli/Documents/Dropbox/The Cooper Union/ArtificialIntelligence/NeuralNetworks/NeuralNet/grades.train", Read);
    ExampleContainer examples = ExampleContainer(trainingFilestream);
    trainingFilestream->close();
    return examples;
}

std::fstream* GetOutputFile()
{
    std::cout << "Please enter the name of the desired output file:" << std::endl;
    return GetFileOpen("OUTPUT", Write);
}

int GetMaxNumberOfEpochs()
{
    std::cout << "Please enter an integer number of epochs for the training:" << std::endl;
    return GetPositiveIntegerInput();
}

double GetLearningRate()
{
    std::cout << "Please enter a floating point number for the learning rate:" << std::endl;
    return GetDoubleInput();
}

int main(int argc, char **argv)
{
    std::cout << "Hello, welcome to NeuralNetwork Training program!!" << std::endl;
    
    ThreeLayerNetwork initialNetwork = LoadInitialNetwork();
    ExampleContainer trainingExamples = LoadTrainingExamples();
    std::fstream* outputFile = GetOutputFile();
    int maxNumEpochs = GetMaxNumberOfEpochs();
    double learningRate = GetLearningRate();
    
    std::list<Example> examples = trainingExamples.GetExamples();
    
    for (int i = 0; i < maxNumEpochs; i++)
    {
	std::list<Example>::iterator ex;
	for (ex = examples.begin(); ex != examples.end(); ex++)
	{
	    initialNetwork.PropogateForward((*ex));
	    initialNetwork.PropogateErrorsBackward((*ex));
	    initialNetwork.UpdateWeights((*ex), learningRate);
	}
    }
    initialNetwork.OutputNetwork(outputFile);
}
