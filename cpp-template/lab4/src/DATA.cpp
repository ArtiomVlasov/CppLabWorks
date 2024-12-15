#include "DATA.hpp"

DATA::DATA(int argc, char** argv) : argc(argc), argv(argv) {
    checkInputArguments();
    for (int i = 1; i < argc - 2; ++i) {
        if (strncmp(argv[i] + strlen(argv[i]) - 4, ".wav", 4) != 0){
            throw std::runtime_error("not .wav file: " + (std::string)argv[i]);
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
            throw std::logic_error("this program [SoundProcessor] modifies the input wav file according to the commands written in the input file with .txt extension\n\n \
            commands that can be used (in file write without []):\nmute [n] [m] - to mute audio from n second to m second\nmix [filenum] [n] [m] - to mix audio with filenum file (filenum type int) from n sec to m sec\nrandom [n] [m] - fill interval from n to m second with random value of samples\n\n \
            syntax of using utilite:\nSoundProcessor <WAV Files pathes... (min 1 file)> <output WAV File path> <todo file path (commands)>\n");
            
        }
    }
    if (argc < 4){
        throw std::runtime_error("need at least 3 arguments!");
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

