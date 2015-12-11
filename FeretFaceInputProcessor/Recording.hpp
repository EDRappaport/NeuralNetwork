#ifndef _RECORDING_H
#define _RECORDING_H

#include <stdio.h>
#include <iostream>

class Recording
{
public:
    Recording(std::string subjectId, std::string basePath, std::string fileRoot, std::string filePath);
    std::string GetFilePath();
    long GetSubjectId();
    
private:
    std::string _filePath;
    long _subjectId;
    
    std::string CreateFilePath(std::string basePath, std::string fileRoot, std::string filePath);
};

#endif