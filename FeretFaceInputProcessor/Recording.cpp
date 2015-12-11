#include "Recording.hpp"

#include <string.h>
#include <iostream> 

Recording::Recording(std::string subjectId, std::string basePath, std::string fileRoot, std::string filePath)
{
    _subjectId = std::stoi(subjectId.substr(4,5));
    _filePath = CreateFilePath(basePath, fileRoot, filePath);
}

std::string Recording::CreateFilePath(std::string basePath, std::string fileRoot, std::string filePath)
{
    std::string fullFilePath = basePath;
    
    if (fileRoot.compare("Disc1") == 0)
    {
	fullFilePath += "/dvd1/";
    }
    else if (fileRoot.compare("Disc2") == 0)
    {
	fullFilePath += "/dvd2/";
    }
    else
    {
	std::cerr << fileRoot << " is not either \'Disc1\' or \'Disc2\'" << std::endl;
    }
    fullFilePath += filePath;
    return fullFilePath;
}

std::string Recording::GetFilePath()
{
    return _filePath;
}

long int Recording::GetSubjectId()
{
    return _subjectId;
}

