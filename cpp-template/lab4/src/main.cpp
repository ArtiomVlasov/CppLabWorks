#include <iostream>
#include <stdexcept>
#include <cstring>
#include "DATA.hpp"
#include "SoundProcessor.hpp"
#include "Comands.hpp"
#include "exeptions.hpp"

int main(int argc, char **argv){
    try {
        DATA data(argc, argv);
        std::vector<Comand> comands;

        readComands(&comands, data.getTodoFile(), (int)data.getInputFiles().size());
        

        SoundProcessor processor(&data, &comands);

        processor.process();
        std::cout << "\nall good!\npath of result file: .\\" << data.getOutputFile() << std::endl;
    }
    catch (const HelpRequestedException& e) {
        std::cout << e.what() << std::endl;
        return 0;
    } 
    catch (const FileOpenException& e) {
        std::cerr << "File error: " << e.what() << std::endl;
        std::cerr << "Please check if the file exists and you have permission to access it." << std::endl;
        return 1;
    } 
    catch (const InvalidCommandArgumentsException& e) {
        std::cerr << "Command error: " << e.what() << std::endl;
        std::cerr << "Please review the commands file for errors." << std::endl;
        return 1;
    } 
    catch (const WAVFormatException& e) {
        std::cerr << "WAV format error: " << e.what() << std::endl;
        std::cerr << "Ensure the input file conforms to the WAV PCM format." << std::endl;
        return 1;
    } 
    catch (const SoundProcessorException& e) {
        std::cerr << "Sound processing error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}