#pragma once
#include <string>
#include <random>
#include <limits>
#include "Comands.hpp"
#include "DATA.hpp"
#include "WAV.hpp"
#include <memory>

// virtual class for fabric 
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



// class ConverterFactory {
// public:
//     virtual std::unique_ptr<Converter> createConverter(Comand* cmd) = 0;
//     virtual ~ConverterFactory() = default;
// };

// class MuteFactory : public ConverterFactory {
// public:
//     std::unique_ptr<Converter> createConverter(Comand* cmd) override {
//         return std::make_unique<Mute>(cmd);
//     }
// };

// class MixFactory : public ConverterFactory {
// private:
//     std::string secondFilePath;
// public:
//     MixFactory(const std::string& filePath) : secondFilePath(filePath) {}
//     std::unique_ptr<Converter> createConverter(Comand* cmd) override {
//         return std::make_unique<Mix>(cmd, secondFilePath);
//     }
// };

// class RandomFactory : public ConverterFactory {
// public:
//     std::unique_ptr<Converter> createConverter(Comand* cmd) override {
//         return std::make_unique<Random>(cmd);
//     }
// };