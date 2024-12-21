#define _CRT_SECURE_NO_WARNINGS
#include "WAV.hpp"
#include "exeptions.hpp"

WAV::WAV(std::string filepath) : filepath(filepath) {}

WAV::~WAV() {}

bool WAV::checkChunk(const char *name, const char *expect)
{
    return std::strncmp(name, expect, 4) == 0;
}

void WAV::checkHeader()
{
    if (!checkChunk(header.riff, "RIFF") || !checkChunk(header.format, "WAVE"))
    {
        throw SoundProcessorException("Not WAV");
    }
    if (header.audioFormat != 1)
    { 
        throw WAVFormatException("not PCM.");
    }

    if (header.numChannels != 1)
    { 
        throw WAVFormatException("not mono canal.");
    }

    if (header.bitsPerSample != 16)
    {
        throw WAVFormatException("not 16 bit per sample");
    }

    if (header.sampleRate != 44100)
    {
        throw WAVFormatException("not 44100 Hz");
    }
}

void WAV::readHeader()
{
    std::ifstream file(filepath, std::ios::binary);
    if (!file)
    {
        throw FileOpenException(filepath);
    }

    file.read((char*)(&header), sizeof(header) - sizeof(unsigned long) - 4);

    int chunkSize;
    char chunkId[4];
    while (file.read(chunkId, 4))
    {
        file.read((char *)(&chunkSize), 4);
        if (checkChunk(chunkId, "data"))
        {
            const char *chunkId_ = "data";
            std::strncpy(header.subchunk2Id, chunkId_, sizeof(header.subchunk2Id));
            header.subchunk2Size = chunkSize;
            break;
        }
        else
        {
            file.seekg(chunkSize, std::ios::cur);
        }

        if (file.eof() || file.fail())
        {
            throw WAVHeaderException("Cant find data chunk!\n");
            break;
        }
    }
    file.close();
}

void WAV::setFileData(size_t startSample, size_t chunkSize)
{
    std::ifstream file(filepath, std::ios::binary);
    if (!file)
    {
        throw FileOpenException(filepath);
    }
    file.seekg(sizeof(WAVHEADER) + startSample * sizeof(short));

    samples.clear();
    samples.resize(chunkSize);

    file.read((char *)(samples.data()), chunkSize * sizeof(short));
    if (file.fail())
    {
        throw FileReadException("error reading samples from " + filepath);
    }
    file.close();
}

std::vector<short> &WAV::getSamples()
{
    return samples;
}

WAV::WAVHEADER WAV::getHeader()
{
    return header;
}

void WAV::copyHeader(WAV *inputWAV)
{
    this->header = inputWAV->header;
}

void WAV::writeOutputHeader(const std::string &filepath_){
    std::ofstream file(filepath_, std::ios::binary);
    if (!file)
    {
        throw FileOpenException( filepath);
    }
    file.write((char*)(&header), sizeof(WAVHEADER));
    file.close();
}

void WAV::writeOutputWAV(const std::string &filepath_)
{
    std::ofstream file(filepath_, std::ios::binary);
    if (!file)
    {
        throw FileOpenException(filepath);
    }

    file.write((char*)(samples.data()), samples.size() * sizeof(short));
    file.close();
}