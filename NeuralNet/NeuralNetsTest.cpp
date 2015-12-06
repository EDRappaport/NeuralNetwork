#include <iostream>
#include <iomanip>
#include <numeric>

#include "InputHelper.hpp"
#include "ThreeLayerNetwork.hpp"
#include "ExampleContainer.hpp"


ExampleContainer LoadTestingExamples()
{
    std::cout << "Please enter the filename for the test file:" << std::endl;
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

int main(int argc, char **argv)
{
    std::cout << "Hello, welcome to NeuralNetwork Testing program!!" << std::endl;
    
    ThreeLayerNetwork initialNetwork = ThreeLayerNetwork::GetNewNetworkFromFile(); //LoadInitialNetwork();
    ExampleContainer testExamples = LoadTestingExamples();
    std::fstream* outputFile = GetOutputFile();
    (*outputFile).setf(std::ios::fixed);
    (*outputFile) << std::setprecision(3);
    
    std::list<Example> examples = testExamples.GetExamples();
    
    std::vector<int> A (testExamples.GetOutputSize(), 0); // expected 1, predicted 1
    std::vector<int> B (testExamples.GetOutputSize(), 0); // expected 0, predicted 1
    std::vector<int> C (testExamples.GetOutputSize(), 0); // expected 1, predicted 0
    std::vector<int> D (testExamples.GetOutputSize(), 0); // expected 0, predicted 0
    
    std::list<Example>::iterator ex;
    for (ex = examples.begin(); ex != examples.end(); ex++)
    {
	initialNetwork.PropogateForward((*ex));
	std::vector<bool> outputs = initialNetwork.GetOutputs();
	std::vector<bool> expectedOutputs = ex->GetOutputs();
	if (outputs.size() != expectedOutputs.size())	
	{
	    std::cerr << "Something weird happened - expectedOutputs size is not the same as the outputs size - this should have been ensured elsewhere!" << std::endl;
	    exit(-1);
	}
	for (int i = 0; i < outputs.size(); i++)
	{
	    if (expectedOutputs[i] == true) //expected 1
	    {
		if (outputs[i] == true) // predicted 1
		{
		    A[i]++;
		}
		else // predicted 0
		{
		    C[i]++;
		}
	    }
	    else // expected 0
	    {
		if (outputs[i] == true) // predicted 1
		{
		    B[i]++;
		}
		else // predicted 0
		{
		    D[i]++;
		}
	    }
	}
    }

    std::vector<double> OverallAccuracy (testExamples.GetOutputSize(), 0);
    std::vector<double> Precision (testExamples.GetOutputSize(), 0);
    std::vector<double> Recall (testExamples.GetOutputSize(), 0);
    std::vector<double> F1 (testExamples.GetOutputSize(), 0);
    
    for (int i = 0; i < testExamples.GetOutputSize(); i++)
    {
	OverallAccuracy[i] = ((double) A[i] + D[i])/(A[i] + B[i] + C[i] + D[i]);
	Precision[i] = (double) A[i]/(A[i] + B[i]);
	Recall[i] = (double) A[i]/(A[i] + C[i]);
	F1[i] = (2*Precision[i]*Recall[i])/(Precision[i] + Recall[i]);
    }
    
    for (int i = 0; i < testExamples.GetOutputSize(); i++)
    {
	(*outputFile) << A[i] << " " << B[i] << " " << C[i] << " " << D[i] << " " << OverallAccuracy[i] << " " << Precision[i]
	    << " " << Recall[i] << " " << F1[i] << std::endl;
    }
    
    int microA = std::accumulate(A.begin(), A.end(), 0);
    int microB = std::accumulate(B.begin(), B.end(), 0);
    int microC = std::accumulate(C.begin(), C.end(), 0);
    int microD = std::accumulate(D.begin(), D.end(), 0);
    
    double microOverallAccuracy = ((double) microA + microD)/(microA + microB + microC + microD);
    double microPrecision = (double) microA/(microA + microB);
    double microRecall = (double) microA/(microA + microC);
    double microF1 = (2*microPrecision*microRecall)/(microPrecision + microRecall);
    
    std::cout << std::accumulate(OverallAccuracy.begin(), OverallAccuracy.end(), 0) << std::endl;
    
    double macroOverallAccuracy = std::accumulate(OverallAccuracy.begin(), OverallAccuracy.end(), 0.0)/ (double) OverallAccuracy.size();
    double macroPrecision = std::accumulate(Precision.begin(), Precision.end(), 0.0)/ (double) Precision.size();
    double macroRecall = std::accumulate(Recall.begin(), Recall.end(), 0.0)/ (double) Recall.size();
    double macroF1 = (2*macroPrecision*macroRecall)/(macroPrecision + macroRecall);
    
    (*outputFile) << microOverallAccuracy << " " << microPrecision << " " << microRecall << " " << microF1 << std::endl;
    (*outputFile) << macroOverallAccuracy << " " << macroPrecision << " " << macroRecall << " " << macroF1 << std::endl;
    
    outputFile->close();
}