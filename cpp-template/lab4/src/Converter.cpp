#include "Converter.hpp"
#include <climits>
#define SAMPLE_RATE 44100


Mute::Mute(Comand *cmd) : startSample(cmd->getArg(0) * SAMPLE_RATE), endSample(cmd->getArg(1) * SAMPLE_RATE){}

void Mute::apply(WAV& file){
    auto& sample = file.getSamples();
    size_t sampleSize = sample.size();
    
    for (size_t i = startSample; i < endSample && i < sampleSize; ++i){
        sample[i] = 0;
    }
    std::cout << "applied mute command. duration: " << startSample/SAMPLE_RATE << " " << endSample/SAMPLE_RATE << std::endl;
}


Mix::Mix(Comand *cmd, const std::string &secondFilePath) : secondFilePath(secondFilePath), startSample(cmd->getArg(1) * SAMPLE_RATE), endSample(cmd->getArg(2) * SAMPLE_RATE) {}

void Mix::apply(WAV& file){
    WAV secondFile(secondFilePath);
    secondFile.setFileData();

    auto& mainSample = file.getSamples();
    const auto& secondSample = secondFile.getSamples();

    for (size_t i = startSample; i < endSample && i < secondSample.size() && i < mainSample.size(); ++i){
        mainSample[i] = (mainSample[i] + secondSample[i]) / 2;
    }
    std::cout << "applied mix command with file: " << secondFilePath << "; duration: " << startSample/SAMPLE_RATE << " " << endSample/SAMPLE_RATE << std::endl;
}

Random::Random(Comand *cmd) : startSample(cmd->getArg(0) * SAMPLE_RATE), endSample(cmd->getArg(1) * SAMPLE_RATE){}

void Random::apply(WAV& file){
    auto& sample = file.getSamples();
    size_t sampleSize = sample.size();
    
    std::random_device rd; 
    std::mt19937 gen(rd()); 

    short min = SHRT_MIN; 
    short max = SHRT_MAX;  

    std::uniform_int_distribution<short> dist(min, max);

    for (size_t i = startSample; i < endSample && i < sampleSize; ++i){
        sample[i] = dist(gen);
    }
    std::cout << "applied random command. duration: " << startSample/SAMPLE_RATE << " " << endSample/SAMPLE_RATE << std::endl;
}
