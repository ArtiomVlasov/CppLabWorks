#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>

class WAV
{
private:
    struct WAVHEADER {
        char riff[4];
        unsigned int chunkSize;
        char format[4];
        char subchunk1Id[4];
        unsigned int subchunk1Size;
        unsigned short audioFormat;
        unsigned short numChannels;
        unsigned int sampleRate;
        unsigned int byteRate;
        unsigned short blockAlign;
        unsigned short bitsPerSample;
        char subchunk2Id[4];
        unsigned long subchunk2Size;
    };

    std::string filepath;
    
    WAVHEADER header;
    bool checkChunk(const char* name, const char* expect);
    void checkHeader ();
   
public:
    WAV(std::string filepath);
    virtual ~WAV();
    std::vector<short> samples;
    void readHeader();
    void writeOutputHeader(const std::string &filepath_);
    void setFileData(size_t startSample, size_t chunkSize);
    std::vector<short>& getSamples();
    WAVHEADER getHeader();
    void copyHeader(WAV* inputWAV);
    void writeOutputWAV(const std::string& filepath);
};


