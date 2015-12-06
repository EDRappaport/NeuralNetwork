#include <iostream>
#include <fstream>

#include "InputHelper.hpp"


std::fstream* InputHelper::GetFileOpen(std::string filename, FileOpenType fileOpenType)
{
    std::ios_base::openmode openMode = fileOpenType == Read ? std::ios::in : std::ios::out;
    while (true)
    {
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

double InputHelper::GetDoubleInput()
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

int InputHelper::GetPositiveIntegerInput()
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
