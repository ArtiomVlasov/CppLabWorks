#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>
#include "source.hpp"

using namespace std;

bool cmp(Words& a, Words& b){
    return (a.getFreq() > b.getFreq());
}

int main(int argc, char* argv[])
{
    if(argc != 3){
        cerr << "Wrong number of Args" << endl;
        return 1;
    }
    int totalWords = 0;
    ifstream input(argv[1]);
    if(!input.is_open()){
        cerr << "Error" << endl;
        return 1;
    }
    map<string, int> mapOfFrequency = readFromFile(input, totalWords);
    vector<Words> sortedWords;
    for (auto& pair : mapOfFrequency) {
        sortedWords.push_back(Words(pair.first, pair.second));
    }
    sort(sortedWords.begin(), sortedWords.end(), cmp);
    ofstream csvOutput(argv[2]);
    if(!csvOutput.is_open()){
        cerr << "Error" << endl;
        return 1;
    }
    csvOutput << "Слово Частота Частота (%)\n";
    writeToCsv(sortedWords, csvOutput, totalWords);
    csvOutput.close();
    input.close();
    return 0;
}
