#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <memory>
#include "DATA.hpp"
#include "WAV.hpp"
#include "Converter.hpp"
#include "Comands.hpp"

class ConverterFactory {
public:
    static std::unique_ptr<Converter> createConverter(Comand *cmd, DATA* data);
};

class SoundProcessor
{
private:
    DATA* data;
    std::vector<Comand> *Comands;
public:
    SoundProcessor(DATA* data, std::vector<Comand> *Comands);
    virtual ~SoundProcessor();
    void process();

};

