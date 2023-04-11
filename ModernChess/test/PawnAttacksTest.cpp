#include "ModernChess/PawnAttacks.h"
#include "ModernChess/Utilities.h"

#include <gtest/gtest.h>

namespace
{
    using namespace ModernChess;
    using namespace Attacks;



    TEST(AttacksGenerationTest, WhitePawnsAttackEast)
    {
        // Occupy White pawnAttackTable on d4
        const BitBoardState whitePawnsBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::d4);

        // White pawnAttackTable should move to e5
        const BitBoardState whitePawnAttackBoard = WhitePawnsAttacks::east(whitePawnsBoard);

        EXPECT_FALSE(BitBoardOperations::isOccupied(whitePawnAttackBoard, Square::d4));

        EXPECT_TRUE(BitBoardOperations::isOccupied(whitePawnAttackBoard, Square::e5));

        print(std::cout, whitePawnAttackBoard) << std::endl;
    }

    TEST(AttacksGenerationTest, WhitePawnsAttackWest)
    {
        // Occupy White pawnAttackTable on d4
        const BitBoardState whitePawnsBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::d4);

        // White pawnAttackTable should move to c5
        const BitBoardState whitePawnAttackBoard = WhitePawnsAttacks::west(whitePawnsBoard);

        EXPECT_FALSE(BitBoardOperations::isOccupied(whitePawnAttackBoard, Square::d4));

        EXPECT_TRUE(BitBoardOperations::isOccupied(whitePawnAttackBoard, Square::c5));

        print(std::cout, whitePawnAttackBoard) << std::endl;
    }

    TEST(AttacksGenerationTest, WhitePawnsAttackTwo)
    {
        // Occupy White pawnAttackTable on d4 & f4
        BitBoardState whitePawnsBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::d4);
        whitePawnsBoard = BitBoardOperations::occupySquare(whitePawnsBoard, Square::f4);

        // Both White pawns attacks e5
        const BitBoardState whitePawnAttackBoard = WhitePawnsAttacks::two(whitePawnsBoard);

        EXPECT_FALSE(BitBoardOperations::isOccupied(whitePawnAttackBoard, Square::d4));
        EXPECT_FALSE(BitBoardOperations::isOccupied(whitePawnAttackBoard, Square::f4));

        // c5 is not attacked by two pawns
        EXPECT_FALSE(BitBoardOperations::isOccupied(whitePawnAttackBoard, Square::c5));
        EXPECT_FALSE(BitBoardOperations::isOccupied(whitePawnAttackBoard, Square::g5));

        // e5 is attacked by two pawns
        EXPECT_TRUE(BitBoardOperations::isOccupied(whitePawnAttackBoard, Square::e5));

        print(std::cout, whitePawnAttackBoard) << std::endl;
    }

    TEST(AttacksGenerationTest, BlackPawnsAttackEast)
    {
        // Occupy White pawnAttackTable on d4
        const BitBoardState blackPawnsBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::d4);

        // Black pawnAttackTable should move to e3
        const BitBoardState blackPawnAttackBoard = BlackPawnsAttacks::east(blackPawnsBoard);

        EXPECT_FALSE(BitBoardOperations::isOccupied(blackPawnAttackBoard, Square::d4));

        EXPECT_TRUE(BitBoardOperations::isOccupied(blackPawnAttackBoard, Square::e3));

        print(std::cout, blackPawnAttackBoard) << std::endl;
    }

    TEST(AttacksGenerationTest, BlackPawnsAttackWest)
    {
        // Occupy White pawnAttackTable on d4
        const BitBoardState blackPawnsBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::d4);

        // Black pawnAttackTable should move to c3
        const BitBoardState blackPawnAttackBoard = BlackPawnsAttacks::west(blackPawnsBoard);

        EXPECT_FALSE(BitBoardOperations::isOccupied(blackPawnAttackBoard, Square::d4));

        EXPECT_TRUE(BitBoardOperations::isOccupied(blackPawnAttackBoard, Square::c3));

        print(std::cout, blackPawnAttackBoard) << std::endl;
    }

    TEST(AttacksGenerationTest, BlackPawnsAttackTwo)
    {
        // Occupy White pawnAttackTable on d4 & f4
        BitBoardState blackPawnsBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::d4);
        blackPawnsBoard = BitBoardOperations::occupySquare(blackPawnsBoard, Square::f4);

        // Both White pawns attacks e3
        const BitBoardState whitePawnAttackBoard = BlackPawnsAttacks::two(blackPawnsBoard);

        EXPECT_FALSE(BitBoardOperations::isOccupied(whitePawnAttackBoard, Square::d4));
        EXPECT_FALSE(BitBoardOperations::isOccupied(whitePawnAttackBoard, Square::f4));

        // c3 is not attacked by two pawns
        EXPECT_FALSE(BitBoardOperations::isOccupied(whitePawnAttackBoard, Square::c3));
        EXPECT_FALSE(BitBoardOperations::isOccupied(whitePawnAttackBoard, Square::g3));

        // e5 is attacked by two pawns
        EXPECT_TRUE(BitBoardOperations::isOccupied(whitePawnAttackBoard, Square::e3));

        print(std::cout, whitePawnAttackBoard) << std::endl;
    }

}


