#include <stdexcept>
#include <string>

class SoundProcessorException : public std::runtime_error
{
public:
    explicit SoundProcessorException(const std::string &message)
        : std::runtime_error(message + "\n") {}
};

class FileException : public SoundProcessorException
{
public:
    explicit FileException(const std::string &message)
        : SoundProcessorException("File error: " + message + "\n") {}
};

class FileOpenException : public FileException
{
public:
    explicit FileOpenException(const std::string &filename)
        : FileException("Failed to open file: " + filename + "\n") {}
};

class FileReadException : public FileException
{
public:
    explicit FileReadException(const std::string &filename)
        : FileException("Failed to read file: " + filename + "\n") {}
};

class FileWriteException : public FileException
{
public:
    explicit FileWriteException(const std::string &filename)
        : FileException("Failed to write in file: " + filename + "\n") {}
};

class WAVFormatException : public SoundProcessorException
{
public:
    explicit WAVFormatException(const std::string &message)
        : SoundProcessorException("WAV format error: " + message + "\n") {}
};

class WAVUnsupportedFormatException : public WAVFormatException
{
public:
    explicit WAVUnsupportedFormatException(const std::string &detail)
        : WAVFormatException("Unsupported audio format: " + detail + "\n") {}
};

class WAVHeaderException : public WAVFormatException
{
public:
    explicit WAVHeaderException(const std::string &detail)
        : WAVFormatException("Header issue: " + detail + "\n") {}
};

class CommandException : public SoundProcessorException
{
public:
    explicit CommandException(const std::string &message)
        : SoundProcessorException("Command error: " + message + "\n") {}
};

class UnknownCommandException : public CommandException
{
public:
    explicit UnknownCommandException(const std::string &command)
        : CommandException("Unknown command: " + command + "\n") {}
};

class InvalidCommandArgumentsException : public CommandException
{
public:
    explicit InvalidCommandArgumentsException(const std::string &detail)
        : CommandException("Invalid arguments " + detail + "\n") {}
};

class ArgumentException : public SoundProcessorException
{
public:
    explicit ArgumentException(const std::string &message)
        : SoundProcessorException("Argument error: " + message + "\n") {}
};

class MissingArgumentException : public ArgumentException
{
public:
    explicit MissingArgumentException()
        : ArgumentException("Required arguments are missing! \n") {}
};

class InvalidFileTypeException : public ArgumentException
{
public:
    explicit InvalidFileTypeException(const std::string &filename)
        : ArgumentException("Invalid file type: " + filename + "\n") {}
};

class HelpRequestedException : public SoundProcessorException
{
public:
    HelpRequestedException()
        : SoundProcessorException("this program [SoundProcessor] modifies the input wav file according to the commands written in the input file with .txt extension\n\n \
            commands that can be used (in file write without []):\nmute [n] [m] - to mute audio from n second to m second\nmix [filenum] [n] [m] - to mix audio with filenum file (filenum type int) from n sec to m sec\nrandom [n] [m] - fill interval from n to m second with random value of samples\n\n \
            syntax of using utilite:\nSoundProcessor <WAV Files pathes... (min 1 file)> <output WAV File path> <todo file path (commands)>\n") {}
};
