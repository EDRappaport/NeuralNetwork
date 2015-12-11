#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>


std::ofstream* GetOutputFile()
{
    std::cout << "Please enter the name of the desired output file:" << std::endl;
    std::string filename = "initialNetwork";
    
    while (true)
    {
	//std::cin >> filename;
	std::ofstream* fileStream = new std::ofstream();
	fileStream->open(filename.c_str());
	if (fileStream->is_open())
	{
	    return fileStream;
	}
	std::cout << "Unable to open file '" << filename << "' - please enter a filename of an openable file:" << std::endl;
    }
}

int main(int argc, char **argv)
{
    srand (time(NULL));
    
    std::ofstream* initialNetworkFilestream = GetOutputFile();
    
    int imageSize = 32*48;// 64*96;
    int hiddenNodeCount = 20;
    
    (*initialNetworkFilestream) << imageSize*2 << " " << hiddenNodeCount << " " << 1 << std::endl;
    
    std::vector<double> offsetWeight(hiddenNodeCount/2); // going to make weights symmetirc
    
    for (int i = 0; i < hiddenNodeCount/2; i++)
    {
	
	double myRand = ((double) rand() / (RAND_MAX));
	offsetWeight[i] = myRand;
	(*initialNetworkFilestream) << offsetWeight[i] << " ";
	
	for (int j = 0; j < imageSize; j++)
	{
	    (*initialNetworkFilestream) << 1 << " "; 
	}
	for (int j = 0; j < imageSize; j++)
	{
	    (*initialNetworkFilestream) << 0 << " "; 
	}
	(*initialNetworkFilestream) << std::endl;
    }
    for (int i = 0; i < hiddenNodeCount/2; i++)
    {
	(*initialNetworkFilestream) << offsetWeight[i] << " ";
	for (int j = 0; j < imageSize; j++)
	{
	    (*initialNetworkFilestream) << 0 << " "; 
	}
	for (int j = 0; j < imageSize; j++)
	{
	    (*initialNetworkFilestream) << 1 << " ";
	}
	(*initialNetworkFilestream) << std::endl;
    }
    
    std::vector<double> outNodeWeights(hiddenNodeCount/2); // going to make weights symmetirc
    (*initialNetworkFilestream) << ((double) rand() / (RAND_MAX)) << " ";
    for (int i = 0; i < hiddenNodeCount/2; i++)
    {
	double myRand = ((double) rand() / (RAND_MAX));
	outNodeWeights[i] = myRand;
	(*initialNetworkFilestream) << outNodeWeights[i] << " ";
    }
    for (int i = 0; i < hiddenNodeCount/2; i++)
    {
	(*initialNetworkFilestream) << outNodeWeights[i] << " ";
    }    
    initialNetworkFilestream->close();
}
