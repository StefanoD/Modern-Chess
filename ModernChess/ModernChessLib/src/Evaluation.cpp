#include "ModernChess/Evaluation.h"

std::ostream &operator<<(std::ostream &os, const ModernChess::EvaluationResult &evalResult)
{
    os << "info score cp " << evalResult.score << " depth " << evalResult.depth << " nodes " << evalResult.numberOfNodes << "\n";
    os << "bestmove " << evalResult.bestMove << "\n";

    return os;
}