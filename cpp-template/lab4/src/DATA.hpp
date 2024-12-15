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
     // FIXME rewrite to another class

    DATA(int argc, char** argv);
    ~DATA();
    const std::vector<std::string> getInputFiles() const;
    const std::string getOutputFile();
    const std::string getTodoFile();
    // const std::vector<Command> getCommands();

private:
    std::vector<std::string> inputFilesPaths;
    std::string outputFilePath;
    std::string todoFilePath;
    // std::vector<Command> commands;
    int argc;
    char** argv;

    void checkInputArguments();

};


