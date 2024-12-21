#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstring>



class DATA
{
public:

    DATA(int argc, char** argv);
    ~DATA();
    const std::vector<std::string> getInputFiles() const;
    const std::string getOutputFile();
    const std::string getTodoFile();
    
private:
    std::vector<std::string> inputFilesPaths;
    std::string outputFilePath;
    std::string todoFilePath;
    int argc;
    char** argv;

    void checkInputArguments();

};


