#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>
#include <map>
#include "DATA.hpp"
#include "WAV.hpp"
#include "Converter.hpp"
#include "Comands.hpp"

class SoundProcessor
{
private:
    DATA* data;
    std::vector<Comand> *Comands;
public:
    SoundProcessor(DATA* data, std::vector<Comand> *Comands);
    virtual ~SoundProcessor();
    void process(std::map<std::string, ConverterFactory*> converterFactoryMap);

};

