#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <vector>
#include "source.hpp"

using namespace std;

bool isSeparator(char c)
{
    if (c == ' ' || c == '.' || c == ',' || c == '?' || c == '!')
    {
        return true;
    }
    return false;
}

list<string> splitWords(string line)
{
    list<string> words;
    string word;
    for (char letter : line)
    {
        if (!isSeparator(letter))
        {
            word += tolower(letter);
        }
        else
        {
            if (!word.empty())
            {
                words.push_back(word);
                word.clear();
            }
        }
    }
    if (!word.empty())
    {
        words.push_back(word);
    }
    return words;
}

map<string, int> readFromFile(ifstream& input, int &totalWords)
{
    list<string> lines;
    map<string, int> mapOfFrequency;

    for (string tmp; getline(input, tmp);)
    {
        list<string> words = splitWords(tmp);
        for (string word : words)
        {
            mapOfFrequency[word]++;
            totalWords++;
        }
    }

    input.close();
    return mapOfFrequency;
}

void writeToCsv(vector<Words> &sortedWords, ofstream& csvOutput, int totalWords)
{
    for (Words p : sortedWords)
    {
        csvOutput << p.getWord() << " " << p.getFreq() << " " << (float(p.getFreq()) / totalWords * 100) << "%" << endl;
    }
    csvOutput.close();
}