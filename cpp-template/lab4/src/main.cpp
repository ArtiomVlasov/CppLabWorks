#include <iostream>
#include <stdexcept>
#include <cstring>
#include "DATA.hpp"
#include "SoundProcessor.hpp"
#include "Comands.hpp"


int main(int argc, char **argv){
    try {
        DATA data(argc, argv);
        std::vector<Comand> comands;

        readComands(&comands, data.getTodoFile(), (int)data.getInputFiles().size());
        

        SoundProcessor processor(&data, &comands);

        processor.process();
        std::cout << "\nall good!\npath of result file: .\\" << data.getOutputFile() << std::endl;
    }
    catch(const std::runtime_error& e){
        std::cerr << "fatal error: " << e.what() << std::endl;
        std::cerr << "type -h to get more info" << std::endl;
        return 1;
    }
    catch (const std::logic_error& e){
        std::cerr << e.what() << std::endl;
        return 0;
    }
    
    return 0;
}