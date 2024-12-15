#pragma once
#include <string>
#include <vector>
#include <stdexcept>
#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <cstring>

class Comand
{
private:
    std::string name;
    std::vector<int> args;

public:
    Comand(std::string name, std::vector<int> args);
    
    int getArg(int i);
    std::string getName();
    ~Comand();
};

void readComands(std::vector<Comand> *Comands, std::string todoFilePath, int inputFilesAmount);