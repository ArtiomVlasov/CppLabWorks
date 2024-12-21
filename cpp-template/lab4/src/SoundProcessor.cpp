#include "SoundProcessor.hpp"
#include "exeptions.hpp"

#define SAMPLE_RATE 44100

SoundProcessor::SoundProcessor(DATA *data, std::vector<Comand> *Comands) : data(data), Comands(Comands) {}

SoundProcessor::~SoundProcessor() {}

void SoundProcessor::process(std::map<std::string, ConverterFactory*>converterFactoryMap)
{
    WAV mainFile(data->getInputFiles()[0]);
    mainFile.readHeader();

    size_t totalSamples = mainFile.getHeader().subchunk2Size / sizeof(short);
    size_t chunkSize = SAMPLE_RATE;
    size_t currentSample = 0;
    mainFile.writeOutputHeader(data->getOutputFile());

    while (currentSample < totalSamples)
    {
        size_t samplesToRead = std::min(chunkSize, totalSamples - currentSample);
        mainFile.setFileData(currentSample, samplesToRead);
        
        for (auto cmd : *Comands)
        {
            auto& converterFactory = converterFactoryMap.at(cmd.getName());
            std::unique_ptr<Converter> converter = converterFactory -> createConverter(&cmd, data);
            converter->apply(mainFile, currentSample);
        }
        std::ofstream outputFile(data->getOutputFile(), std::ios::binary | std::ios::app);
        if (!outputFile)
        {
            throw FileOpenException(data->getOutputFile());
        }

        outputFile.write(reinterpret_cast<const char *>(mainFile.getSamples().data()),
                         samplesToRead * sizeof(short));

        if (!outputFile)
        {
            throw FileWriteException(data->getOutputFile());
        }

        currentSample += samplesToRead;
    }
}
