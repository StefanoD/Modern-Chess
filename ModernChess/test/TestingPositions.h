#pragma once

namespace ModernChess::TestingPositions {
    // Positions from https://www.chessprogramming.org/Perft_Results

    constexpr auto Position2 = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";
    constexpr auto Position3 = "8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1";
    constexpr auto Position4 = "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1";
    constexpr auto Position5 = "rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8";
    constexpr auto Position6 = "r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10";

    //Test positions where Null Move may fail due to Zugzwang
    // @see https://www.chessprogramming.org/Null_Move_Test-Positions
    constexpr auto Zugzwang1 = "8/8/p1p5/1p5p/1P5p/8/PPP2K1p/4R1rk w - - 0 1"; // best move Rf1
    constexpr auto Zugzwang2 = "1q1k4/2Rr4/8/2Q3K1/8/8/8/8 w - - 0 1"; // best move Kh6
    constexpr auto Zugzwang3 = "7k/5K2/5P1p/3p4/6P1/3p4/8/8 w - - 0 1"; // best move g5
    constexpr auto Zugzwang4 = "8/6B1/p5p1/Pp4kp/1P5r/5P1Q/4q1PK/8 w - - 0 32"; // best move Qxh4
    constexpr auto Zugzwang5 = "8/8/1p1r1k2/p1pPN1p1/P3KnP1/1P6/8/3R4 b - - 0 1"; // best move Nxd5
    // From https://web.archive.org/web/20071031095933/http://www.brucemo.com/compchess/programming/nullmove.htm
    constexpr auto Zugzwang6 = "6k1/pp6/2p5/3p4/3Pp1p1/2P1PpPq/PPQ2P2/3R2K1 w - - 0 1"; // White can do any move. Black moves Qg2
}