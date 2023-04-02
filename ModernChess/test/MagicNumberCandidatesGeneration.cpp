#include <gtest/gtest.h>

#include <iostream>

namespace
{
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
        const auto n1 = (uint64_t)(getRandomU32Number() & 0xFFFF);
        const auto n2 = (uint64_t)(getRandomU32Number() & 0xFFFF);
        const auto n3 = (uint64_t)(getRandomU32Number() & 0xFFFF);
        const auto n4 = (uint64_t)(getRandomU32Number() & 0xFFFF);

        // return random number
        return n1 | (n2 << 16) | (n3 << 32) | (n4 << 48);
    }

    // generate magic number candidate
    uint64_t generateMagicNumber()
    {
        return getRandomU64Number() & getRandomU64Number() & getRandomU64Number();
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
}

