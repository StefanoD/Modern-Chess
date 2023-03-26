#include "ModernChess/AttacksGeneration.h"
#include "ModernChess/PawnAttackGeneration.h"
#include "ModernChess/PawnQueries.h"
#include "ModernChess/Utilities.h"

#include <gtest/gtest.h>

namespace
{
    using namespace ModernChess;
    using namespace AttackGeneration;


    TEST(AttacksGenerationTest, WhitePawnsAbleToCaptureEast)
    {
        // Occupy White pawnAttackTable on d4
        const BitBoardState whitePawnsBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::d4);

        // Occupy Black figure on e5
        const BitBoardState blackFiguresBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::e5);

        const bool ableToCaptureEast = WhitePawnsQueries::ableToCaptureEast(whitePawnsBoard, blackFiguresBoard);

        EXPECT_TRUE(ableToCaptureEast);
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

    TEST(AttacksGenerationTest, BlackPawnsAbleToCaptureEast)
    {
        // Occupy White pawnAttackTable on d4
        const BitBoardState blackPawnsBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::d4);

        // Occupy Black figure on e3
        const BitBoardState whiteFiguresBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::e3);

        const bool ableToCaptureEast = BlackPawnsQueries::ableToCaptureEast(blackPawnsBoard, whiteFiguresBoard);

        EXPECT_TRUE(ableToCaptureEast);
    }

}


