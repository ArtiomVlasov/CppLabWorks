#include "Converter.hpp"
#include <climits>
#define SAMPLE_RATE 44100

Mute::Mute(Comand *cmd) : startSample(cmd->getArg(0) * SAMPLE_RATE), endSample(cmd->getArg(1) * SAMPLE_RATE) {}

void Mute::apply(WAV &file, size_t currentSample)
{
    auto &sample = file.getSamples();
    if (currentSample >= startSample && currentSample <= endSample)
    {
        for (int i = 0; i < (int)sample.size(); i++)
        {
            sample[i] = 0;
        }
    }
    if (currentSample == endSample)
    {
        std::cout << "applied mute command. duration: " << startSample / SAMPLE_RATE << " " << endSample / SAMPLE_RATE << std::endl;
    }
}

Mix::Mix(Comand *cmd, const std::string &secondFilePath) : secondFilePath(secondFilePath), startSample(cmd->getArg(1) * SAMPLE_RATE), endSample(cmd->getArg(2) * SAMPLE_RATE) {}

void Mix::apply(WAV &file, size_t currentSample)
{
    if (currentSample >= startSample && currentSample <= endSample)
    {
        WAV secondFile(secondFilePath);
        secondFile.readHeader();
        size_t chunkSize = SAMPLE_RATE; // 1 секунда аудио
        size_t samplesToRead = std::min(chunkSize, endSample - currentSample);
        secondFile.setFileData(currentSample, samplesToRead);
        auto &mainSamples = file.getSamples();
        auto &secondSamples = secondFile.getSamples();
        for (size_t i = 0; i < samplesToRead; i++)
        {
            mainSamples[i] = (mainSamples[i] + secondSamples[i]) / 2;
        }
    }
    if (currentSample == endSample) // После обработки последнего чанка
    {
        std::cout << "applied mix command with file: " << secondFilePath << "; duration: " << startSample/SAMPLE_RATE << " " << endSample/SAMPLE_RATE << std::endl;
    }
}

Random::Random(Comand *cmd) : startSample(cmd->getArg(0) * SAMPLE_RATE), endSample(cmd->getArg(1) * SAMPLE_RATE) {}

void Random::apply(WAV &file, size_t currentSample)
{
    auto &sample = file.getSamples();
    size_t sampleSize = sample.size();

    std::random_device rd;
    std::mt19937 gen(rd());

    short min = SHRT_MIN;
    short max = SHRT_MAX;

    std::uniform_int_distribution<short> dist(min, max);

    if (currentSample >= startSample && currentSample <= endSample)
    {
        for (size_t i = 0; i < sampleSize; i++)
        {
            sample[i] = dist(gen);
        }
    }
     if (currentSample == endSample) // После обработки последнего чанка
    {
         std::cout << "applied random command. duration: " << startSample / SAMPLE_RATE << " " <<  endSample/SAMPLE_RATE << std::endl;
    }
}
