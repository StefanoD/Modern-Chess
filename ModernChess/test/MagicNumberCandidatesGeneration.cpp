#include "ModernChess/BitBoardOperations.h"
#include "ModernChess/RookAttackGeneration.h"
#include "ModernChess/BishopAttackGeneration.h"
#include "ModernChess/Figure.h"

#include <gtest/gtest.h>

#include <iostream>
#include <array>

namespace {
    using namespace ModernChess;

    /**
     * @return generates 32-bit pseudo legal numbers
     */
    uint32_t getRandomU32Number()
    {
        // pseudo random number state
        static uint32_t state = 1804289383;

        // get current state
        uint32_t number = state;

        // XOR shift algorithm
        number ^= number << 13;
        number ^= number >> 17;
        number ^= number << 5;

        // update random number state
        state = number;

        // return random number
        return number;
    }

    // generate 64-bit pseudo legal numbers
    uint64_t getRandomU64Number()
    {
        // init random numbers slicing 16 bits from MS1B side
        const auto n1 = uint64_t(getRandomU32Number()) & 0xFFFF;
        const auto n2 = uint64_t(getRandomU32Number()) & 0xFFFF;
        const auto n3 = uint64_t(getRandomU32Number()) & 0xFFFF;
        const auto n4 = uint64_t(getRandomU32Number()) & 0xFFFF;

        // return random number
        return n1 | (n2 << 16) | (n3 << 32) | (n4 << 48);
    }

    // generate magic number candidate
    uint64_t generateMagicNumber()
    {
        return getRandomU64Number() & getRandomU64Number() & getRandomU64Number();
    }

    // find appropriate magic number
    uint64_t findMagicNumber(Square square, uint32_t relevantBits, FigureTypes figure)
    {
        // init occupancies
        std::array<uint64_t, 4096> occupancies{};

        // init attack tables
        std::array<uint64_t, 4096> attacks{};

        // init used attacks
        std::array<uint64_t, 4096> usedAttacks{};

        // init attack mask for a current piece
        const uint64_t attackMask = FigureTypes::Bishop == figure ? BishopAttackHelperFunctions::maskBishopAttacks(square) :
                                    RookAttackHelperFunctions::maskRookAttacks(square);

        // init occupancy indices
        const uint32_t occupancyIndices = 1 << relevantBits;

        // loop over occupancy indices
        for (uint32_t index = 0; index < occupancyIndices; index++)
        {
            // init occupancies
            occupancies.at(index) = BitBoardOperations::setOccupancy(index, relevantBits, attackMask);

            // init attacks
            if (FigureTypes::Bishop == figure)
            {
                attacks.at(index) = BishopAttackHelperFunctions::bishopAttacksOnTheFly(occupancies.at(index),
                                                                                           square);
            }
            else
            {
                attacks.at(index) = RookAttackHelperFunctions::rookAttacksOnTheFly(occupancies.at(index), square);
            }
        }

        // test magic numbers loop
        constexpr uint32_t maxRetries = 100000000;

        for (uint32_t randomCount = 0; randomCount < maxRetries; ++randomCount)
        {
            // generate magic number candidate
            const uint64_t magicNumber = generateMagicNumber();

            // skip inappropriate magic numbers
            if (BitBoardOperations::countBits((attackMask * magicNumber) & 0xFF00000000000000) < 6) 
            {
                continue;
            }

            // reset used attacks
            usedAttacks = {};

            // init index & fail flag
            uint32_t index;
            bool fail;

            // test magic index loop
            for (index = 0, fail = false; !fail && index < occupancyIndices; index++)
            {
                // init magic index
                const uint32_t magicIndex = (occupancies.at(index) * magicNumber) >> (64 - relevantBits);

                // if magic index works
                if (usedAttacks.at(magicIndex) == 0ULL)
                {    // init used attacks
                    usedAttacks.at(magicIndex) = attacks.at(index);
                }
                else if (usedAttacks.at(magicIndex) != attacks.at(index))
                {    // magic index doesn't work, because of collision
                    fail = true;
                }
            }

            if (!fail) {
                // if magic number works return it
                return magicNumber;
            }
        }

        // if magic number doesn't work
        std::cout << "Magic number failed!" << std::endl;
        return 0ULL;
    }

    // init magic numbers
    void initMagicNumbers()
    {
        std::cout << "Rook Magic Numbers:" << std::endl;

        // loop over 64 board squares
        for (int i = 0; i < 64; ++i)
        {    // init rook magic numbers
            const Square square{i};
            std::cout << "0x" << std::hex << findMagicNumber(square,
                                                             RookAttackHelperFunctions::RookMetaData::relevantBits.at(square),
                                                             FigureTypes::Rook) << "ULL, " << std::endl;
        }

        std::cout << std::endl << std::endl;
        std::cout << "Bishop Magic Numbers:" << std::endl;

        // loop over 64 board squares
        for (int i = 0; i < 64; ++i)
        {    // init bishop magic numbers
            const Square square{i};
            std::cout << "0x" << std::hex << findMagicNumber(square,
                                                             BishopAttackHelperFunctions::BishopMetaData::relevantBits.at(square),
                                                             FigureTypes::Bishop) << "ULL, " << std::endl;
        }
    }

    TEST(UtilitiesTest, getRandomU32Number)
    {
        EXPECT_EQ(getRandomU32Number(), 1741896308);
        EXPECT_EQ(getRandomU32Number(), 321584506);
        EXPECT_EQ(getRandomU32Number(), 3694591032);
        EXPECT_EQ(getRandomU32Number(), 1972257248);
        EXPECT_EQ(getRandomU32Number(), 200407065);
    }

    TEST(UtilitiesTest, generateMagicNumber)
    {
        EXPECT_EQ(generateMagicNumber(), 27162335321796624);
    }

    TEST(UtilitiesTest, initMagicNumbers)
    {
        initMagicNumbers();
    }
}

