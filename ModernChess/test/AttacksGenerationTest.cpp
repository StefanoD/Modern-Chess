#include "ModernChess/AttacksGeneration.h"
#include "ModernChess/Utilities.h"

#include <gtest/gtest.h>

namespace
{
    using namespace ModernChess;

    TEST(AttacksGenerationTest, RookNorthAttacks)
    {
        // Occupy rooks on a1 and h2
        BitBoardState whiteRooksBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::a1);
        whiteRooksBoard = BitBoardOperations::occupySquare(whiteRooksBoard, Square::h2);

        // Occupy figures on a7 and h6
        BitBoardState playBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::a7);
        playBoard = BitBoardOperations::occupySquare(playBoard, Square::h6);

        // Seem not to be necessary, but the attacking pieces are usually also part of the play board
        playBoard |= whiteRooksBoard;

        // We need to pass a rayAttackBoard with empty squares as second parameter where the bits are set to 1
        const BitBoardState emptySquaresBoard = ~playBoard;
        const BitBoardState rayAttackBoard = AttacksGeneration::northAttacks(whiteRooksBoard, emptySquaresBoard);

        const std::vector<Square> attackRay {
                a2, a3, a4, a5, a6, a7, // attacks from the left rook
                    h3, h3, h4, h5, h6 // attacks from the right rook
        };

        const std::vector<Square> notAttackedSquares {
                a1, b1, c1, d1, e1, f1, g1, h1,
                    b2, c2, d2, e2, f2, g2, h2,
                    b3, c3, d3, e3, f3, g3,
                    b4, c4, d4, e4, f4, g4,
                    b5, c5, d5, e5, f5, g5,
                    b6, c6, d6, e6, f6, g6,
                    b7, c7, d7, e7, f7, g7, h7,
                a8, b8, c8, d8, e8, f8, g8, h8
        };

        for (const Square square : attackRay)
        {
            EXPECT_TRUE(BitBoardOperations::isOccupied(rayAttackBoard, square));
        }

        for (const Square square : notAttackedSquares)
        {
            EXPECT_FALSE(BitBoardOperations::isOccupied(rayAttackBoard, square));
        }

        print(std::cout, rayAttackBoard) << std::endl;
    }


}


