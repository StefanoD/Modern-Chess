Observations
--------------

# Move Sorting/Scoring
## Killer Moves
Normally a killer move is only stored when 
- if (score >= beta)
- the move is a non-capture.

For some reasons the second condition performs worse in my tests than always storing
killer moves as soo the condition `score >= beta` is true.

## History Moves
Performs in some tests of mine much worse than
(`EvaluationTest, PreventPotentialMateIn5ForWhite`) when enabled.