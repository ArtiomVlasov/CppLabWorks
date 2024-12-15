#pragma once
#include <string>
#include <random>
#include <limits>
#include "Comands.hpp"
#include "DATA.hpp"
#include "WAV.hpp"

// virtual class for fabric 
class Converter
{
private:
public:
    virtual void apply(WAV& wavFile) = 0;
    virtual ~Converter() = default;
};

class Mute final : public Converter{
private:
    size_t startSample;
    size_t endSample;
public:
    Mute(Comand *cmd);
    void apply(WAV& file);
    virtual ~Mute() = default;
};

class Mix final : public Converter{
private:
    std::string secondFilePath;
    size_t startSample;
    size_t endSample;
public:
    Mix(Comand *cmd, const std::string &secondFilePath);
    void apply(WAV& file);
    virtual ~Mix() = default;
};


class Random final : public Converter{
private:
    size_t startSample;
    size_t endSample;
public:
    Random(Comand *cmd);
    void apply(WAV& file);
    virtual ~Random() = default;
};