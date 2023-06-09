#include "TestingPositions.h"
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

    TEST(UCICommunicationTest, FindCheckMateInOne)
    {
        /*
         * 8 ♔ . . . . . . .
         * 7 . . ♙ ♗ ♘ . . .
         * 6 . . ♘ ♞ ♙ . . .
         * 5 . . . ♙ . . . .
         * 4 ♞ . ♖ ♟︎ . . ♟︎ .
         * 3 ♟︎ ♛ ♖ . ♟︎ . . .
         * 2 . ♝ ♕ . . ♟︎ . ♟︎
         * 1 . . . . ♚ . . ♜
         *
         *   a b c d e f g h
         */
        std::stringstream inputStream;
        std::stringstream outputStream;
        std::stringstream errorStream;

        UCICommunication uciCom(inputStream, outputStream, errorStream);

        std::thread communicationThread([&uciCom]{
            uciCom.startCommunication();
        });

        constexpr auto fenString = "k7/2pbn3/2nNp3/3p4/N1rP2P1/PQr1P3/1Bq2P1P/4K2R w K - 0 26";

        inputStream << "position fen " << fenString << "\n";
        inputStream << "go depth 6\n";
        inputStream << "quit\n";
        communicationThread.join();

        const std::string engineOutput{outputStream.str()};

        EXPECT_TRUE(engineOutput.find("bestmove b3b7") != std::string::npos);
        std::cout << engineOutput << std::endl;
    }

    TEST(UCICommunicationTest, MateIn5ForWhite)
    {
        /*
         * 8 ♖ . . . ♖ . ♔ .
         * 7 . . ♙ . ♕ ♙ ♟︎ ♙
         * 6 ♙ . ♘ . . ♘ . ♛
         * 5 . . . . ♙ . ♞ .
         * 4 . . . ♙ ♟︎ . ♗ .
         * 3 ♙ ♟︎ . ♟︎ . . . .
         * 2 ♟︎ . ♟︎ . . ♟︎ ♟︎ .
         * 1 . . ♚ ♜ . ♝ . ♜
         *
         *   a b c d e f g h
         */
        std::stringstream inputStream;
        std::stringstream outputStream;
        std::stringstream errorStream;

        UCICommunication uciCom(inputStream, outputStream, errorStream);

        std::thread communicationThread([&uciCom]{
            uciCom.startCommunication();
        });

        constexpr auto fenString = "r3r1k1/2p1qpPp/p4n1Q/4p1N1/1n1pP1b1/pP1P4/P1P2PP1/2KR1B1R w - - 5 18";

        inputStream << "position fen " << fenString << "\n";
        inputStream << "go depth 6\n";
        inputStream << "quit\n";
        communicationThread.join();

        const std::string engineOutput{outputStream.str()};

        EXPECT_TRUE(engineOutput.find("bestmove g5h7") != std::string::npos);
        std::cout << engineOutput << std::endl;
    }

    TEST(UCICommunicationTest, ManyMoves)
    {
        /*
         * 8 ♖ . . . . . . .
         * 7 ♙ . . ♜ . ♙ . ♙
         * 6 . ♙ ♗ . . . ♙ ♔
         * 5 . . . . ♝ . . .
         * 4 ♟︎ . . . . ♟︎ . .
         * 3 . ♟︎ . . . . . .
         * 2 . . ♟︎ ♚ . ♘ ♟︎ ♟︎
         * 1 . . . . . ♝ . .
         *
         *   a b c d e f g h
         */
        std::stringstream inputStream;
        std::stringstream outputStream;
        std::stringstream errorStream;

        UCICommunication uciCom(inputStream, outputStream, errorStream);

        std::thread communicationThread([&uciCom]{
            uciCom.startCommunication();
        });

        constexpr auto fenString = "position startpos moves a2a4 g7g6 d2d4 f8g7 e2e4 e7e5 d4e5 g7e5 g1f3 d8f6 f3e5 f6e5 b1c3 g8f6 f2f4 e5a5 d1d4 a5b6 d4e5 b6e6 e5c7 b8c6 e4e5 e8g8 c7d6 e6d6 e5d6 c6d4 e1d1 d4f5 b2b3 f5d6 c1a3 f6e4 c3e4 d6e4 a3f8 e4f2 d1d2 f2h1 f8d6 h1f2 a1e1 b7b6 e1e8 g8g7 e8e7 c8b7 d6e5 g7h6 e7d7 b7c6";

        inputStream << fenString << "\n";
        inputStream << "go depth 6\n";
        inputStream << "quit\n";
        communicationThread.join();

        const std::string engineOutput{outputStream.str()};

        EXPECT_TRUE(engineOutput.find("bestmove d7f7") != std::string::npos);
        std::cout << engineOutput << std::endl;

        std::cout << uciCom.getGameState() << std::endl;
    }

    TEST(UCICommunicationTest, Zugzwang3)
    {
        /*
         * 8 . . . . . . . ♔
         * 7 . . . . . ♚ . .
         * 6 . . . . . ♟︎ . ♙
         * 5 . . . ♙ . . . .
         * 4 . . . . . . ♟︎ .
         * 3 . . . ♙ . . . .
         * 2 . . . . . . . .
         * 1 . . . . . . . .
         *
         *   a b c d e f g h
         */
        std::stringstream inputStream;
        std::stringstream outputStream;
        std::stringstream errorStream;

        UCICommunication uciCom(inputStream, outputStream, errorStream);

        std::thread communicationThread([&uciCom]{
            uciCom.startCommunication();
        });

        inputStream << "position fen " << TestingPositions::Zugzwang3 << "\n";
        inputStream << "go depth 6\n";
        inputStream << "quit\n";
        communicationThread.join();

        const std::string engineOutput{outputStream.str()};

        EXPECT_TRUE(engineOutput.find("bestmove f7e7") != std::string::npos);
        std::cout << engineOutput << std::endl;

        std::cout << uciCom.getGameState() << std::endl;
    }
}