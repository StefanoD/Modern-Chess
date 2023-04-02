#pragma once

#include "BitBoardConstants.h"
#include <ostream>

std::ostream& print(std::ostream& os, const ModernChess::BitBoardState bitBoardState);

/**
 * @return generates 32-bit pseudo legal numbers
 */
[[nodiscard]] uint32_t getRandomNumber();
