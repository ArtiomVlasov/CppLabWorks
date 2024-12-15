#include "SoundProcessor.hpp"

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
    mainFile.setFileData();

    for (auto cmd : *Comands){ //FIXME переписать последовательный конвертер на применение сразу всех
        std::unique_ptr<Converter> converter = ConverterFactory::createConverter(&cmd, data);
        if (converter) {
            converter->apply(mainFile);
        } else {
            std::cerr << "Unknown command type: " << cmd.getName() << std::endl;
        }
    }

    mainFile.writeOutputWAV(data->getOutputFile());
}


