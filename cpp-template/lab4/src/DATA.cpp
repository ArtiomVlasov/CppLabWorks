#include "DATA.hpp"
#include "exeptions.hpp"

DATA::DATA(int argc, char** argv) : argc(argc), argv(argv) {
    checkInputArguments();
    for (int i = 1; i < argc - 2; ++i) {
        if (strncmp(argv[i] + strlen(argv[i]) - 4, ".wav", 4) != 0){
            throw InvalidFileTypeException("not .wav file: " + (std::string)argv[i]);
        }
        inputFilesPaths.push_back(argv[i]);
    }
    outputFilePath = argv[argc - 2];
    todoFilePath = argv[argc - 1];
}
DATA::~DATA() {}



void DATA::checkInputArguments(){
    for (int i = 1; i < argc; ++i)
    {
        if (!std::strcmp(argv[i], "-h")){
            throw HelpRequestedException();
            
        }
    }
    if (argc < 4){
        throw ArgumentException("need at least 3 arguments!");
    }
}

const std::vector<std::string> DATA::getInputFiles() const{
    return inputFilesPaths;
}
const std::string DATA::getOutputFile(){
    return outputFilePath;
}
const std::string DATA::getTodoFile(){
    return todoFilePath;
}

