#include "Comands.hpp"
#include "exeptions.hpp"

Comand::Comand(std::string name, std::vector<int> args) : name(name), args(args) {}

int Comand::getArg(int i) { return args[i]; }
std::string Comand::getName() { return name; }
Comand::~Comand() {}

void readComands(std::vector<Comand> *Comands, std::string todoFilePath, int inputFilesAmount)
{
    std::ifstream file(todoFilePath);
    if (!file)
    {
        throw FileOpenException(todoFilePath);
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
                    throw InvalidCommandArgumentsException(
                        "for mute: " + std::to_string(start) + std::to_string(end) +"\nwarning on line: " + std::to_string(lineCount));
                }
            }
            else
            {
                throw InvalidCommandArgumentsException(
                   ": cannot read values for mute command!\ncommand will be not applied \nwarning on line: " + std::to_string(lineCount)
                   );
            }
        }
        else if (command == "mix")
        {
            int filenum, start, end;
            if (iss >> filenum >> start >> end)
            {
                if (filenum < 1 || filenum > inputFilesAmount)
                {
                    throw InvalidCommandArgumentsException(
                    ": invalid number of file for mix command: " + std::to_string(filenum) + "\nthis command will be not applied\n" + "warning on line: " + std::to_string(lineCount));
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
                   throw InvalidCommandArgumentsException("for mix: " + std::to_string(start) + std::to_string(end) +"\nwarning on line: " + std::to_string(lineCount));
                }
            }
            else
            {
                throw InvalidCommandArgumentsException(
                   ": cannot read values for mix command!\ncommand will be not applied \nwarning on line: " + std::to_string(lineCount)
                   );
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
                    throw InvalidCommandArgumentsException("for random: " + std::to_string(start) + std::to_string(end) +"\nwarning on line: " + std::to_string(lineCount));
                }
            }
            else
            {
                throw InvalidCommandArgumentsException(
                   ": cannot read values for random command!\ncommand will be not applied \nwarning on line: " + std::to_string(lineCount)
                   );
            }
        }
        else
        {
            std::cout << "\nexeption on line: " << lineCount << std::endl;
            throw UnknownCommandException(command +  "\nexeption on line: " + std::to_string(lineCount));
        }
        args.clear();
        lineCount++;
    }
    file.close();
}