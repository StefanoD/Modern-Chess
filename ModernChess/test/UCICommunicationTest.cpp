#include "ModernChess/UCICommunication.h"
#include "ModernChess/FenParsing.h"

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

        const GameState gameState = uciCom.getGameState();
        const GameState expectedGameState = FenParsing::FenParser(FenParsing::startPosition).parse();

        EXPECT_TRUE(gameState == expectedGameState);

        const std::string engineOutput{outputStream.str()};

        std::cout << engineOutput << std::endl;
    }

    TEST(UCICommunicationTest, sendStartingPositionAndMakeMoves)
    {
        std::stringstream inputStream;
        std::stringstream outputStream;
        std::stringstream errorStream;

        UCICommunication uciCom(inputStream, outputStream, errorStream);

        std::thread communicationThread([&]{
            uciCom.startCommunication();
        });

        inputStream << "position startpos moves a2a3 a7a6\n";
        inputStream << "quit\n";

        communicationThread.join();

        const GameState gameState = uciCom.getGameState();

        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::WhitePawn], Square::a2));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Both], Square::a2));

        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::WhitePawn], Square::a3));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Both], Square::a3));

        const std::string engineOutput{outputStream.str()};

        std::cout << engineOutput << std::endl;
    }

    TEST(UCICommunicationTest, ParseFENPosition)
    {

        std::stringstream inputStream;
        std::stringstream outputStream;
        std::stringstream errorStream;

        UCICommunication uciCom(inputStream, outputStream, errorStream);

        std::thread communicationThread([&]{
            uciCom.startCommunication();
        });

        inputStream << "position fen " << FenParsing::startPosition << " moves a2a3 a7a6\n";
        inputStream << "quit\n";
        communicationThread.join();

        const GameState gameState = uciCom.getGameState();

        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::WhitePawn], Square::a2));
        EXPECT_FALSE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Both], Square::a2));

        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.bitboards[Figure::WhitePawn], Square::a3));
        EXPECT_TRUE(BitBoardOperations::isOccupied(gameState.board.occupancies[Color::Both], Square::a3));

        const std::string engineOutput{outputStream.str()};

        std::cout << engineOutput << std::endl;
    }

    TEST(UCICommunicationTest, sendGoCommand)
    {
        std::stringstream inputStream;
        std::stringstream outputStream;
        std::stringstream errorStream;

        UCICommunication uciCom(inputStream, outputStream, errorStream);

        std::thread communicationThread([&]{
            uciCom.startCommunication();
        });

        inputStream << "position startpos\n";
        inputStream << "go\n";
        inputStream << "quit\n";

        communicationThread.join();
    }

    TEST(UCICommunicationTest, sendGoWithDepthCommand)
    {
        std::stringstream inputStream;
        std::stringstream outputStream;
        std::stringstream errorStream;

        UCICommunication uciCom(inputStream, outputStream, errorStream);

        std::thread communicationThread([&]{
            uciCom.startCommunication();
        });

        inputStream << "position startpos\n";
        inputStream << "go depth 2\n";
        inputStream << "quit\n";

        communicationThread.join();
    }

    TEST(UCICommunicationTest, TrickyPosition)
    {
        std::stringstream inputStream;
        std::stringstream outputStream;
        std::stringstream errorStream;

        UCICommunication uciCom(inputStream, outputStream, errorStream);

        std::thread communicationThread([&]{
            uciCom.startCommunication();
        });

        constexpr auto fenString = "k7/2pbn3/r1nNp3/3p4/N2P2P1/PQ2P3/1B3P1P/4K2R w K - 7 26";

        inputStream << "position fen " << fenString << "\n";
        inputStream << "go depth 6\n";
        inputStream << "quit\n";
        communicationThread.join();

        const std::string engineOutput{outputStream.str()};

        std::cout << engineOutput << std::endl;
    }
}