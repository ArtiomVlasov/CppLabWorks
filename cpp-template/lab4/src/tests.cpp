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
class MockWAV : public WAV {
public:
    MockWAV() : WAV("mock") {
        samples = std::vector<short>(44100, 1000);
    }
    void setSamples(const std::vector<short>& newSamples) { samples = newSamples; }
    std::vector<short>& getSamples() { return samples; }
};

TEST(MuteTest, ApplyMuteCommand) {
    Comand muteCmd("mute", {0, 1});
    Mute mute(&muteCmd);
    MockWAV wav;

    mute.apply(wav, 0);

    auto samples = wav.getSamples();
    EXPECT_EQ(samples[0], 0); 
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