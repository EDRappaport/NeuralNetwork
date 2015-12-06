#ifndef _INPUTHELPER_H
#define _INPUTHELPER_H

enum FileOpenType {Read, Write};

class InputHelper
{
public:    
    static std::fstream* GetFileOpen(std::string filename, FileOpenType fileOpenType);
    
    static double GetDoubleInput();
    static int GetPositiveIntegerInput();
};

#endif