#pragma once
#include <string>
#include <random>
#include <limits>
#include "Comands.hpp"
#include "Data.hpp"
#include "WAV.hpp"
#include <memory>

class Converter
{
private:
public:
    virtual void apply(WAV& wavFile, size_t currentSample) = 0;
    virtual ~Converter() = default;
};

class Mute final : public Converter{
private:
    size_t startSample;
    size_t endSample;
public:
    Mute(Comand *cmd);
    void apply(WAV& file, size_t currentSample);
    virtual ~Mute() = default;
};

class Mix final : public Converter{
private:
    std::string secondFilePath;
    size_t startSample;
    size_t endSample;
public:
    Mix(Comand *cmd, const std::string &secondFilePath);
    void apply(WAV& file, size_t currentSample);
    virtual ~Mix() = default;
};


class Random final : public Converter{
private:
    size_t startSample;
    size_t endSample;
public:
    Random(Comand *cmd);
    void apply(WAV& file, size_t currentSample);
    virtual ~Random() = default;
};

class ConverterFactory {
public:
    virtual std::unique_ptr<Converter> createConverter(Comand* cmd, DATA *data) = 0;
    virtual ~ConverterFactory() = default;
};

class MuteFactory : public ConverterFactory {
public:
    std::unique_ptr<Converter> createConverter(Comand* cmd, DATA *data) override {
        return std::make_unique<Mute>(cmd);
    }
};

class MixFactory : public ConverterFactory {
public:
    std::unique_ptr<Converter> createConverter(Comand* cmd, DATA *data) override {
        return std::make_unique<Mix>(cmd,  data->getInputFiles()[cmd->getArg(0)]);
    }
};

class RandomFactory : public ConverterFactory {
public:
    std::unique_ptr<Converter> createConverter(Comand* cmd, DATA *data) override {
        return std::make_unique<Random>(cmd);
    }
};