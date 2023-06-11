#pragma once

#include <cinttypes>

namespace ModernChess {
    class PseudoRandomGenerator
    {
    public:
        PseudoRandomGenerator() = delete;

        static constexpr uint32_t initialState = 1804289383;

        /**
        * @return generates 32-bit pseudo legal numbers
        */
        static uint32_t getRandomU32Number()
        {
            // pseudo random number state
            static uint32_t state = initialState;

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

        /// generate 64-bit pseudo legal numbers
        static uint64_t getRandomU64Number()
        {
            // init random numbers slicing 16 bits from MS1B side
            const auto n1 = uint64_t(getRandomU32Number()) & 0xFFFF;
            const auto n2 = uint64_t(getRandomU32Number()) & 0xFFFF;
            const auto n3 = uint64_t(getRandomU32Number()) & 0xFFFF;
            const auto n4 = uint64_t(getRandomU32Number()) & 0xFFFF;

            // return random number
            return n1 | (n2 << 16) | (n3 << 32) | (n4 << 48);
        }
    };
}