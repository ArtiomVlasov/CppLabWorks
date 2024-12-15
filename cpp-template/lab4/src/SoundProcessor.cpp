#include "SoundProcessor.hpp"
#define SAMPLE_RATE 44100

std::unique_ptr<Converter> ConverterFactory::createConverter(Comand *cmd, DATA *data) {
        if (cmd->getName() == "mute") {
            return std::make_unique<Mute>(cmd);
        } else if (cmd->getName() == "mix") {
            return std::make_unique<Mix>(cmd, data->getInputFiles()[cmd->getArg(0)]);
        } else if (cmd->getName() == "random") {
            return std::make_unique<Random>(cmd);
        }
        return nullptr; 
}

SoundProcessor::SoundProcessor(DATA* data, std::vector<Comand> *Comands) : data(data), Comands(Comands){}



SoundProcessor::~SoundProcessor() {}

void SoundProcessor::process(){
    WAV mainFile(data->getInputFiles()[0]);
    mainFile.readHeader();

    size_t totalSamples = mainFile.getHeader().subchunk2Size / sizeof(short); // Total number of samples
    size_t chunkSize = SAMPLE_RATE; // 1 second of audio (assuming 1 channel, 16-bit samples)
    size_t currentSample = 0;
    mainFile.writeOutputHeader(data->getOutputFile());
    



    while (currentSample < totalSamples) {
        size_t samplesToRead = std::min(chunkSize, totalSamples - currentSample); // Avoid reading past the end
        mainFile.setFileData(currentSample, samplesToRead);

        // Apply all commands to the current chunk
        for (auto cmd : *Comands) {
            std::unique_ptr<Converter> converter = ConverterFactory::createConverter(&cmd, data);
            if (converter) {
                converter->apply(mainFile, currentSample);
            } else {
                std::cerr << "Unknown command type: " << cmd.getName() << std::endl;
            }
        }
        std::ofstream outputFile(data->getOutputFile(), std::ios::binary | std::ios::app);
        if (!outputFile) {
            throw std::runtime_error("Error opening output file: " + data->getOutputFile());
        }

        outputFile.write(reinterpret_cast<const char *>(mainFile.getSamples().data()),
                         samplesToRead * sizeof(short));
                         
        if (!outputFile) {
            throw std::runtime_error("Error writing to output file: " + data->getOutputFile());
        }

        currentSample += samplesToRead;
    }
}


