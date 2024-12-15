#include <gtest/gtest.h>
#include "Comands.hpp"
#include "Converter.hpp"
#include "WAV.hpp"
#include "DATA.hpp"
#include "SoundProcessor.hpp"

TEST(ComandTest, ConstructorTest) {
    std::vector<int> args = {10, 20};
    Comand cmd("mute", args);

    EXPECT_EQ(cmd.getName(), "mute");
    EXPECT_EQ(cmd.getArg(0), 10);
    EXPECT_EQ(cmd.getArg(1), 20);
}

TEST(ComandTest, InvalidArgAccess) {
    std::vector<int> args = {5};
    Comand cmd("random", args);

    EXPECT_THROW(cmd.getArg(1), std::out_of_range);
}

// Mock WAV class
class MockWAV : public WAV {
public:
    MockWAV() : WAV("mock") {
        samples = std::vector<short>(44100, 1000); // 1 секунда аудио, все сэмплы = 1000
    }
    void setSamples(const std::vector<short>& newSamples) { samples = newSamples; }
    std::vector<short>& getSamples() { return samples; }
};

TEST(MuteTest, ApplyMuteCommand) {
    Comand muteCmd("mute", {0, 1}); // mute от 0 до 1 секунды
    Mute mute(&muteCmd);
    MockWAV wav;

    mute.apply(wav, 0); // применить на текущем чанке

    auto samples = wav.getSamples();
    EXPECT_EQ(samples[0], 0); // сэмплы обнулены
    EXPECT_EQ(samples[1000], 0);
}

TEST(RandomTest, ApplyRandomCommand) {
    Comand randomCmd("random", {0, 1});
    Random random(&randomCmd);
    MockWAV wav;

    random.apply(wav, 0);

    auto samples = wav.getSamples();
    bool isRandom = false;
    for (auto s : samples) {
        if (s != 1000) { // сэмплы изменились
            isRandom = true;
            break;
        }
    }
    EXPECT_TRUE(isRandom);
}

TEST(DATA_Test, ValidInputArguments) {
    const char* argv[] = {"program", "file1.wav", "file2.wav", "output.wav", "commands.txt"};
    int argc = 5;

    EXPECT_NO_THROW(DATA data(argc, const_cast<char**>(argv)));
}

TEST(DATA_Test, InvalidInputArguments) {
    const char* argv[] = {"program", "file1.txt", "output.wav", "commands.txt"};
    int argc = 4;

    EXPECT_THROW(DATA data(argc, const_cast<char**>(argv)), std::runtime_error);
}

TEST(DATA_Test, GetFilePaths) {
    const char* argv[] = {"program", "file1.wav", "output.wav", "commands.txt"};
    int argc = 4;

    DATA data(argc, const_cast<char**>(argv));

    EXPECT_EQ(data.getInputFiles().size(), 1);
    EXPECT_EQ(data.getOutputFile(), "output.wav");
    EXPECT_EQ(data.getTodoFile(), "commands.txt");
}

TEST(SoundProcessorTest, ProcessMuteCommand) {
    const char* argv[] = {"program", "input.wav", "output.wav", "commands.txt"};
    int argc = 4;

    // Создание временных файлов
    std::ofstream inputWAV("input.wav", std::ios::binary);
    std::ofstream commands("commands.txt");
    commands << "mute 0 1" << std::endl;

    inputWAV.close();
    commands.close();

    // Тестирование
    DATA data(argc, const_cast<char**>(argv));
    std::vector<Comand> comands;

    readComands(&comands, data.getTodoFile(), data.getInputFiles().size());
    SoundProcessor processor(&data, &comands);

    EXPECT_NO_THROW(processor.process());

    // Проверка вывода (опционально)
    std::ifstream outputWAV("output.wav", std::ios::binary);
    EXPECT_TRUE(outputWAV.good());
    outputWAV.close();
}
