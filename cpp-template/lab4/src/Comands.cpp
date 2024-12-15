#include "Comands.hpp"

Comand::Comand(std::string name, std::vector<int> args) : name(name), args(args) {}

int Comand::getArg(int i) { return args[i]; }
std::string Comand::getName() { return name; }
Comand::~Comand() {}

void readComands(std::vector<Comand> *Comands, std::string todoFilePath, int inputFilesAmount)
{
    std::ifstream file(todoFilePath);
    if (!file)
    {
        throw std::runtime_error("error opening todo file" + todoFilePath);
    }

    std::string line;
    size_t lineCount = 1;
    std::vector<int> args;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string command;
        iss >> command;
        if (command == "mute")
        {
            
            int start, end;
            if (iss >> start >> end)
            {
                
                if (start < 0)
                {
                    std::cout << "in mute command detected negative start second " << start << "\nwill be applied from 0 second" << std::endl;
                    std::cout << "warning on line: " << lineCount << std::endl
                              << std::endl;
                    start = 0;
                }
                
                if (start < end)
                {
                    
                    args.push_back(start);
                    args.push_back(end);
                    Comands->push_back(Comand(command, args));
                }
                else
                {
                    std::cerr << "invalid arguments for mute " << start << end << std::endl;
                    std::cout << "warning on line: " << lineCount << std::endl
                              << std::endl;
                }
            }
            else
            {
                std::cerr << "cannot read values for mute command!\ncommand will be not applied " << std::endl;
                std::cout << "warning on line: " << lineCount << std::endl
                          << std::endl;
            }
        }
        else if (command == "mix")
        {
            int filenum, start, end;
            if (iss >> filenum >> start >> end)
            {
                if (filenum < 1 || filenum > inputFilesAmount)
                {
                    std::cerr << "invalid number of file for mix command: " << filenum << "\nthis command will be not applied\n";
                    std::cout << "warning on line: " << lineCount << std::endl
                              << std::endl;
                    continue;
                }
                if (start < 0)
                {
                    std::cout << "in mix command detected negative start second " << start << "\nwill be applied from 0 second" << std::endl;
                    std::cout << "warning on line: " << lineCount << std::endl
                              << std::endl;
                    start = 0;
                }
                if (start < end)
                {
                    args.push_back(filenum);
                    args.push_back(start);
                    args.push_back(end);
                    Comands->push_back(Comand(command, args));
                }
                else
                {
                    std::cerr << "invalid arguments for mix " << filenum << " " << start << " " << end << std::endl;
                    std::cout << "warning on line: " << lineCount << std::endl
                              << std::endl;
                }
            }
            else
            {
                std::cerr << "cannot read values for mix command!\ncommand will be not applied" << std::endl;
                std::cout << "warning on line: " << lineCount << std::endl
                          << std::endl;
            }
        }
        else if (command == "random")
        {
            int start, end;
            if (iss >> start >> end)
            {
                if (start < 0)
                {
                    std::cout << "in random command detected negative start second " << start << "\nwill be applied from 0 second" << std::endl;
                    std::cout << "warning on line: " << lineCount << std::endl
                              << std::endl;
                    start = 0;
                }
                if (start < end)
                {
                    args.push_back(start);
                    args.push_back(end);
                    Comands->push_back(Comand(command, args));
                }
                else
                {
                    std::cerr << "invalid arguments for random " << start << " " << end << std::endl;
                    std::cout << "warning on line: " << lineCount << std::endl
                              << std::endl;
                }
            }
            else
            {
                std::cerr << "cannot read values for random command!\ncommand will be not applied" << std::endl;
                std::cout << "warning on line: " << lineCount << std::endl
                          << std::endl;
            }
        }
        else
        {
            std::cout << "\nexeption on line: " << lineCount << std::endl;
            throw std::runtime_error("unknown command " + command);
        }
        lineCount++;
    }
    file.close();
}