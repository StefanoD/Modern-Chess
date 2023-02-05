#pragma once

#include <cinttypes>
#include <concepts>

namespace ModernChess {

    /**
     * @brief Wrapped uint64_t representation which makes it type safe.
     *        It has also an overloaded stream operator which print the
     *        single bits as a chess board representation.
     */
    struct BitBoardState
    {
        constexpr BitBoardState() = default;
        constexpr ~BitBoardState() = default;
        constexpr BitBoardState(uint64_t state) : m_state(state){}
        constexpr BitBoardState(const BitBoardState &bitBoardState) = default;
        constexpr BitBoardState(BitBoardState &&) = default;

        constexpr BitBoardState &operator=(BitBoardState state)
        {
            m_state = state.m_state;
            return *this;
        }

        constexpr BitBoardState operator~() const
        {
            return {~m_state};
        }

        template<typename Number>
        requires std::integral<Number>
        constexpr BitBoardState operator<<(const Number shift) const
        {
            return {m_state << shift};
        }

        template<typename Number>
        requires std::integral<Number>
        constexpr BitBoardState operator>>(const Number shift) const
        {
            return {m_state >> shift};
        }

        constexpr BitBoardState operator&(const BitBoardState bitBoardState) const
        {
            return {m_state & bitBoardState.m_state};
        }

        constexpr BitBoardState operator|(const BitBoardState bitBoardState) const
        {
            return {m_state | bitBoardState.m_state};
        }

        template<typename Number>
        requires std::integral<Number>
        constexpr BitBoardState operator*(const Number multiplicator) const
        {
            return {m_state * multiplicator};
        }

        constexpr BitBoardState operator+(const BitBoardState bitBoardState) const
        {
            return {m_state + bitBoardState.m_state};
        }

        template<typename Number>
        constexpr BitBoardState operator+(const Number summand) const
        {
            return {m_state + summand};
        }

        constexpr void operator|=(const BitBoardState bitBoardState)
        {
            m_state |= bitBoardState.m_state;
        }

        constexpr void operator&=(const BitBoardState bitBoardState)
        {
            m_state &= bitBoardState.m_state;
        }

        constexpr bool operator==(const BitBoardState bitBoardState) const
        {
            return m_state == bitBoardState.m_state;
        }

        constexpr bool operator!=(const BitBoardState bitBoardState) const
        {
            return m_state != bitBoardState.m_state;
        }

        constexpr bool operator==(const uint64_t bitBoardState) const
        {
            return m_state == bitBoardState;
        }

        constexpr bool operator!=(const uint64_t bitBoardState) const
        {
            return m_state != bitBoardState;
        }

    private:
        uint64_t m_state{};
    };

    template<typename Number>
    requires std::integral<Number>
    BitBoardState operator*(Number x, const BitBoardState& y)
    {
        return y * x;
    }

    template<typename Number>
    requires std::integral<Number>
    BitBoardState operator+(Number x, const BitBoardState& y)
    {
        return y + x;
    }
}