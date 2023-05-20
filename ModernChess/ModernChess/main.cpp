#include "ModernChess/UCICommunication.h"

#include <iostream>

using namespace ModernChess;

int main()
{
    UCICommunication uciCommunication(std::cin, std::cout, std::cerr);

    uciCommunication.startCommunication();

    return 0;
}