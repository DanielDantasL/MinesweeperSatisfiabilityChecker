#ifndef MINESWEEPERSATISFIABILITYCHECKER_MINESWEEPERBOT_H
#define MINESWEEPERSATISFIABILITYCHECKER_MINESWEEPERBOT_H

# include "MinesweeperInstance.h"

class MinesweeperBot {
public:
    int ChooseCellToReveal(MinesweeperInstance instance);

private:
    int CalculateInstanceScore(MinesweeperInstance instance);
};


#endif //MINESWEEPERSATISFIABILITYCHECKER_MINESWEEPERBOT_H
