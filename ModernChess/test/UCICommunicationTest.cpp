#include "ModernChess/UCICommunication.h"

#include <gtest/gtest.h>

#include <sstream>
#include <thread>

namespace
{
    using namespace ModernChess;
    using namespace std::chrono_literals;

    TEST(UCICommunicationTest, registration)
    {
        std::stringstream inputStream;
        std::stringstream outputStream;
        std::stringstream errorStream;

        UCICommunication uciCom(inputStream, outputStream, errorStream);

        std::thread communicationThread([&]{
            uciCom.startCommunication();
        });

        inputStream << "quit\n";

        communicationThread.join();

        const std::string engineOutput{outputStream.str()};

        EXPECT_TRUE(engineOutput.starts_with("id name Modern Chess"));
        EXPECT_TRUE(engineOutput.find("id author Stefano Di Martino") != std::string::npos);
        EXPECT_TRUE(engineOutput.find("uciok") != std::string::npos);

        std::cout << engineOutput << std::endl;
    }

    TEST(UCICommunicationTest, sendReady)
    {
        std::stringstream inputStream;
        std::stringstream outputStream;
        std::stringstream errorStream;

        UCICommunication uciCom(inputStream, outputStream, errorStream);

        std::thread communicationThread([&]{
            uciCom.startCommunication();
        });

        inputStream << "isready\n";
        inputStream << "quit\n";

        communicationThread.join();

        const std::string engineOutput{outputStream.str()};

        EXPECT_TRUE(engineOutput.find("readyok") != std::string::npos);

        std::cout << engineOutput << std::endl;
    }

    TEST(UCICommunicationTest, sendStartingPosition)
    {
        std::stringstream inputStream;
        std::stringstream outputStream;
        std::stringstream errorStream;

        UCICommunication uciCom(inputStream, outputStream, errorStream);

        std::thread communicationThread([&]{
            uciCom.startCommunication();
        });

        inputStream << "position startpos\n";
        inputStream << "quit\n";

        communicationThread.join();

        const std::string engineOutput{outputStream.str()};

        const std::string expectedDebugOutput = """8 ♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖\n"
                                                "  7 ♙ ♙ ♙ ♙ ♙ ♙ ♙ ♙\n"
                                                "  6 . . . . . . . .\n"
                                                "  5 . . . . . . . .\n"
                                                "  4 . . . . . . . .\n"
                                                "  3 . . . . . . . .\n"
                                                "  2 ♟\uFE0E ♟\uFE0E ♟\uFE0E ♟\uFE0E ♟\uFE0E ♟\uFE0E ♟\uFE0E ♟\uFE0E\n"
                                                "  1 ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜\n"
                                                "\n"
                                                "    a b c d e f g h""";

        EXPECT_TRUE(engineOutput.find(expectedDebugOutput) != std::string::npos);

        std::cout << engineOutput << std::endl;
    }
}