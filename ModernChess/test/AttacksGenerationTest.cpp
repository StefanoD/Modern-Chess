#include "ModernChess/AttacksGeneration.h"
#include "ModernChess/Utilities.h"

#include <gtest/gtest.h>

namespace
{
    using namespace ModernChess;

    TEST(AttacksGenerationTest, RookNorthAttacks)
    {
        // Occupy rooks on a1, h2, g8
        BitBoardState whiteRooksBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::a1);
        whiteRooksBoard = BitBoardOperations::occupySquare(whiteRooksBoard, Square::h2);
        // Edge case: rook is on g8 which is already the most north position
        whiteRooksBoard = BitBoardOperations::occupySquare(whiteRooksBoard, Square::g8);

        // Occupy figures on a7 and h6
        BitBoardState playBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::a7);
        playBoard = BitBoardOperations::occupySquare(playBoard, Square::h6);

        // Seem not to be necessary, but the attacking pieces are usually also part of the play board
        playBoard |= whiteRooksBoard;

        // We need to pass a rayAttackBoard with empty squares as second parameter where the bits are set to 1
        const BitBoardState emptySquaresBoard = ~playBoard;
        const BitBoardState rayAttackBoard = RookAttack::north(whiteRooksBoard, emptySquaresBoard);

        const std::vector<Square> attackRay {
                a2, a3, a4, a5, a6, a7, // attacks from the left rook
                    h3, h4, h5, h6 // attacks from the right rook
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

    TEST(AttacksGenerationTest, RookSouthAttacks)
    {
        // Occupy rooks on a8, h7, g1
        BitBoardState whiteRooksBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::a8);
        whiteRooksBoard = BitBoardOperations::occupySquare(whiteRooksBoard, Square::h7);
        // Edge case: rook is on g1 which is already the most south position
        whiteRooksBoard = BitBoardOperations::occupySquare(whiteRooksBoard, Square::g1);

        // Occupy figures on a2 and h3
        BitBoardState playBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::a2);
        playBoard = BitBoardOperations::occupySquare(playBoard, Square::h3);

        // Seem not to be necessary, but the attacking pieces are usually also part of the play board
        playBoard |= whiteRooksBoard;

        // We need to pass a rayAttackBoard with empty squares as second parameter where the bits are set to 1
        const BitBoardState emptySquaresBoard = ~playBoard;
        const BitBoardState rayAttackBoard = RookAttack::south(whiteRooksBoard, emptySquaresBoard);

        const std::vector<Square> attackRay {
                a2, a3, a4, a5, a6, a7, // attacks from the left rook
                h3, h4, h5, h6 // attacks from the right rook
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

    TEST(AttacksGenerationTest, RookEastAttacks)
    {
        // Occupy rooks on b1, a8, h7
        BitBoardState whiteRooksBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::b1);
        whiteRooksBoard = BitBoardOperations::occupySquare(whiteRooksBoard, Square::a8);
        // Edge case: rook is on h7 which is already the most east position
        whiteRooksBoard = BitBoardOperations::occupySquare(whiteRooksBoard, Square::h7);

        // Occupy figures on f1 and h8
        BitBoardState playBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::f1);
        playBoard = BitBoardOperations::occupySquare(playBoard, Square::h8);

        // Seem not to be necessary, but the attacking pieces are usually also part of the play board
        playBoard |= whiteRooksBoard;

        // We need to pass a rayAttackBoard with empty squares as second parameter where the bits are set to 1
        const BitBoardState emptySquaresBoard = ~playBoard;
        const BitBoardState rayAttackBoard = RookAttack::east(whiteRooksBoard, emptySquaresBoard);

        const std::vector<Square> attackRay {
                    c1, d1, e1, f1,
                b8, c8, d8, e8, f8, g8, h8
        };

        const std::vector<Square> notAttackedSquares {
                a1, b1,                 g1, h1,
                    b2, c2, d2, e2, f2, g2, h2,
                    b3, c3, d3, e3, f3, g3,
                    b4, c4, d4, e4, f4, g4,
                    b5, c5, d5, e5, f5, g5,
                    b6, c6, d6, e6, f6, g6,
                    b7, c7, d7, e7, f7, g7, h7,
                a8,
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

    TEST(AttacksGenerationTest, RookWestAttacks)
    {
        // Occupy rooks on g1, h8, a7
        BitBoardState whiteRooksBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::g1);
        whiteRooksBoard = BitBoardOperations::occupySquare(whiteRooksBoard, Square::h8);
        // Edge case: rook is on a7 which is already the most west position
        whiteRooksBoard = BitBoardOperations::occupySquare(whiteRooksBoard, Square::a7);

        // Occupy figures on a1 and a8
        BitBoardState playBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::a8);
        playBoard = BitBoardOperations::occupySquare(playBoard, Square::a1);

        // Seem not to be necessary, but the attacking pieces are usually also part of the play board
        playBoard |= whiteRooksBoard;

        // We need to pass a rayAttackBoard with empty squares as second parameter where the bits are set to 1
        const BitBoardState emptySquaresBoard = ~playBoard;
        const BitBoardState rayAttackBoard = RookAttack::west(whiteRooksBoard, emptySquaresBoard);

        const std::vector<Square> attackRay {
                a1, b1, c1, d1, e1, f1,
                a8, b8, c8, d8, e8, f8, g8
        };

        const std::vector<Square> notAttackedSquares {
                                     g1, h1,
                 b2, c2, d2, e2, f2, g2, h2,
                 b3, c3, d3, e3, f3, g3,
                 b4, c4, d4, e4, f4, g4,
                 b5, c5, d5, e5, f5, g5,
                 b6, c6, d6, e6, f6, g6,
                 b7, c7, d7, e7, f7, g7, h7, h8
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

    TEST(AttacksGenerationTest, BishopNorthEastAttacks)
    {
        // Occupy bishop on b2
        const BitBoardState whiteRooksBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::b2);

        // Occupy figures on h8
        BitBoardState playBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::h8);

        // Seem not to be necessary, but the attacking pieces are usually also part of the play board
        playBoard |= whiteRooksBoard;

        // We need to pass a rayAttackBoard with empty squares as second parameter where the bits are set to 1
        const BitBoardState emptySquaresBoard = ~playBoard;
        const BitBoardState rayAttackBoard = BishopAttack::northEast(whiteRooksBoard, emptySquaresBoard);

        const std::vector<Square> attackRay {
                c3, d4, e5, f6, g7, h8
        };

        const std::vector<Square> notAttackedSquares {
                a1, b1, c1, d1, e1, f1, g1, h1,
                a2, b2, c2, d2, e2, f2, g2, h2,
                a3, b3,     d3, e3, f3, g3, h3,
                a4, b4, c4,     e4, f4, g4, h4,
                a5, b5, c5, d5,     f5, g5, h5,
                a6, b6, c6, d6, e6,     g6, h6,
                a7, b7, c7, d7, e7, f7,     h7,
                a8, b8, c8, d8, e8, f8, g8,
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

    TEST(AttacksGenerationTest, BishopSouthEastAttacks)
    {
        // Occupy bishop on b7
        const BitBoardState whiteRooksBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::b7);

        // Occupy figures on h1
        BitBoardState playBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::h1);

        // Seem not to be necessary, but the attacking pieces are usually also part of the play board
        playBoard |= whiteRooksBoard;

        // We need to pass a rayAttackBoard with empty squares as second parameter where the bits are set to 1
        const BitBoardState emptySquaresBoard = ~playBoard;
        const BitBoardState rayAttackBoard = BishopAttack::southEast(whiteRooksBoard, emptySquaresBoard);

        const std::vector<Square> attackRay {
                c6, d5, e4, f3, g2, h1
        };

        const std::vector<Square> notAttackedSquares {
                a1, b1, c1, d1, e1, f1, g1,
                a2, b2, c2, d2, e2, f2,     h2,
                a3, b3, c3, d3, e3,     g3, h3,
                a4, b4, c4, d4,     f4, g4, h4,
                a5, b5, c5,     e5, f5, g5, h5,
                a6, b6,     d6, e6, f6, g6, h6,
                a7, b7, c7, d7, e7, f7, g7, h7,
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

    TEST(AttacksGenerationTest, BishopSouthWestAttacks)
    {
        // Occupy bishop on g7
        const BitBoardState whiteRooksBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::g7);

        // Occupy figures on a1
        BitBoardState playBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::a1);

        // Seem not to be necessary, but the attacking pieces are usually also part of the play board
        playBoard |= whiteRooksBoard;

        // We need to pass a rayAttackBoard with empty squares as second parameter where the bits are set to 1
        const BitBoardState emptySquaresBoard = ~playBoard;
        const BitBoardState rayAttackBoard = BishopAttack::southWest(whiteRooksBoard, emptySquaresBoard);

        const std::vector<Square> attackRay {
                f6, e5, d4, c3, b2, a1
        };

        const std::vector<Square> notAttackedSquares {
                    b1, c1, d1, e1, f1, g1, h1,
                a2,     c2, d2, e2, f2, g2, h2,
                a3, b3,     d3, e3, f3, g3, h3,
                a4, b4, c4,     e4, f4, g4, h4,
                a5, b5, c5, d5,     f5, g5, h5,
                a6, b6, c6, d6, e6,     g6, h6,
                a7, b7, c7, d7, e7, f7, g7, h7,
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

    TEST(AttacksGenerationTest, BishopNorthWestAttacks)
    {
        // Occupy bishop on g2
        const BitBoardState whiteRooksBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::g2);

        // Occupy figures on a8
        BitBoardState playBoard = BitBoardOperations::occupySquare(BoardState::empty, Square::a8);

        // Seem not to be necessary, but the attacking pieces are usually also part of the play board
        playBoard |= whiteRooksBoard;

        // We need to pass a rayAttackBoard with empty squares as second parameter where the bits are set to 1
        const BitBoardState emptySquaresBoard = ~playBoard;
        const BitBoardState rayAttackBoard = BishopAttack::northWest(whiteRooksBoard, emptySquaresBoard);

        const std::vector<Square> attackRay {
                a8, b7, c6, d5, e4, f3,
        };

        const std::vector<Square> notAttackedSquares {
                a1, b1, c1, d1, e1, f1, g1, h1,
                a2, b2, c2, d2, e2, f2, g2, h2,
                a3, b3, c3, d3, e3,     g3, h3,
                a4, b4, c4, d4,     f4, g4, h4,
                a5, b5, c5,     e5, f5, g5, h5,
                a6, b6,     d6, e6, f6, g6, h6,
                a7,     c7, d7, e7, f7, g7, h7,
                    b8, c8, d8, e8, f8, g8, h8
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


