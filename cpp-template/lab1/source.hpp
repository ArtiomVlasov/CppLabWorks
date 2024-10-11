#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <iostream>

class Words
{
private:
    std::string word;
    int frequency;

public:
    Words(const std::string& word, int frequency) : word(word), frequency(frequency) {}
    int getFreq() const
    {
        return frequency;
    }
    std::string getWord() const
    {
        return word;
    }
};

void writeToCsv(std::vector<Words> &sortedWords, std::ofstream& csvFile, int totalWords);

std::map<std::string, int> readFromFile(std::ifstream& inputFile, int &totalWords);