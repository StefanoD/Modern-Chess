To Do
--------

## Evaluation
- Static Exchange Evaluation
- Sorting within negamax where the scoring is done within the move generator, might be more efficient. 
  Here the `Move` struct needs an additional property `score`. 
- Use KI (maybe evolutionary algorithms?) to find best MVV-LVA matrix
- Look more into move ordering: https://www.chessprogramming.org/Move_Ordering
- Do not use Late Move Reduction for more conditions like Passed 
  Pawn Moves: https://www.chessprogramming.org/Late_Move_Reductions