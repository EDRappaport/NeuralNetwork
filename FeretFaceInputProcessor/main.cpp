#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

#include <opencv2/opencv.hpp>

#include "pugixml.hpp"

#include "Recording.hpp"

std::ofstream* GetOutputFile(bool isTraining)
{
    std::cout << "Please enter the name of the desired output file:" << std::endl;
    std::string filename = isTraining ? "OUT_TRAIN" : "OUT_TEST";
    
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
    
    std::string xmlDocFile = "/home/elli/Documents/colorferet/dvd1/data/ground_truths/xml/recordings.xml";
    std::string basePath = "/home/elli/Documents/colorferet/";
    
    std::ofstream* outputTrainingFilestream = GetOutputFile(true);
    std::ofstream* outputTestFilestream = GetOutputFile(false);
    
    pugi::xml_document doc;
    if (!doc.load_file(xmlDocFile.c_str()))
    {
	std::cerr << "Failed to load XML doc \'" << xmlDocFile << "\'" << std::endl;
	exit(-1);
    }
    
    std::list<Recording> recordingList;    
    pugi::xml_node recordingsNode = doc.child("Recordings");
    pugi::xml_object_range<pugi::xml_named_node_iterator> recordingsIterator = doc.child("Recordings").children("Recording");
    for (pugi::xml_named_node_iterator it = recordingsIterator.begin(); it != recordingsIterator.end(); it++)
    {
	std::string fileRoot = (*it).child("URL").attribute("root").value();
	std::string filePathWithExtension = (*it).child("URL").attribute("relative").value();
	std::string filePath = filePathWithExtension.substr(0, filePathWithExtension.length()-4);
	std::string subject = (*it).child("Subject").attribute("id").value();
	
	Recording newRecording = Recording(subject, basePath, fileRoot, filePath);
	
	if (newRecording.GetSubjectId() < 5)
	{
	    // to keep this small only going to kee the forst 45 ppl
	    recordingList.push_back(newRecording);
	}
    }
    
    int width = 32;
    int height = 48;
    std::cout << recordingList.size() << std::endl;
    cv::Size desiredImageSize (width, height);
    
    int counter = 0;
    
    int trainingCount = 0;
    int testingCount = 0;
    int totalCounts = recordingList.size()*recordingList.size();
    int proposedTrainingCount = (double) totalCounts * 0.7;
    std::cout << proposedTrainingCount <<std::endl;
    int proposedTestingCount = totalCounts-proposedTrainingCount;
    
    (*outputTestFilestream) << proposedTestingCount << " " << width*height*2 << " " << 1 << std::endl;
    (*outputTrainingFilestream) << proposedTrainingCount << " " << width*height*2 << " " << 1 << std::endl;
    
    (*outputTestFilestream).setf(std::ios::fixed);
    (*outputTestFilestream) << std::setprecision(3);
    (*outputTrainingFilestream).setf(std::ios::fixed);
    (*outputTrainingFilestream) << std::setprecision(3);
    
    for (std::list<Recording>::iterator itOuter = recordingList.begin(); itOuter != recordingList.end(); itOuter++)
    {
	counter++;
	
	if(counter%10 == 0)
	{
	    std::cout << counter << std::endl;
	}
	
	cv::Mat currentImage = cv::imread(itOuter->GetFilePath(), cv::IMREAD_GRAYSCALE);
	cv::Mat resizedCurrentImage;
	cv::resize(currentImage, resizedCurrentImage, desiredImageSize, 0, 0, CV_INTER_AREA);
	//std::cout << "Current Size: " << resizedCurrentImage.size() << std::endl;
	for (std::list<Recording>::iterator itInner = recordingList.begin(); itInner != recordingList.end(); itInner++)
	{
	    cv::Mat currentInnerImage = cv::imread(itInner->GetFilePath(), cv::IMREAD_GRAYSCALE);
	    cv::Mat resizedInnerImage;
	    cv::resize(currentInnerImage, resizedInnerImage, desiredImageSize, 0, 0, CV_INTER_AREA);	    
	    
	    std::ofstream* outputFilestream;
	    double myRand = ((double) rand() / (RAND_MAX));
	    if ((myRand < 0.7 && trainingCount < proposedTrainingCount)|| testingCount >=proposedTestingCount)
	    {
		outputFilestream  = outputTrainingFilestream;
		trainingCount++;
	    }
	    else
	    {
		outputFilestream = outputTestFilestream;
		testingCount++;
	    }
	    	    
	    for (int x = 0; x < width; x++)
	    {
		for (int y = 0; y < height; y++)
		{
		    cv::Scalar intensity = resizedCurrentImage.at<uchar>(x,y);
		    (*outputFilestream) << (double) intensity[0]/255 << " ";
		}
	    }
	    for (int x = 0; x < width; x++)
	    {
		for (int y = 0; y < height; y++)
		{
		    cv::Scalar intensity = resizedInnerImage.at<uchar>(x,y);
		    (*outputFilestream) << (double) intensity[0]/255 << " ";
		}
	    }
	    
	    if (itOuter->GetSubjectId() == itInner->GetSubjectId())
	    {
		(*outputFilestream) << 1;
	    }
	    else
	    {
		(*outputFilestream) << 0;
	    }
	    (*outputFilestream) << std::endl;
	}
    }
    
    std::cout << trainingCount << " " << testingCount << std::endl;
    
    outputTestFilestream->close();
    outputTrainingFilestream->close();
}
