#include <iostream>
#include "MinesweeperInstance.h"
#include "MinesweeperBot.h"

static bool IsViable(MinesweeperInstance instance) {
    for (int i = 0; i < instance.Columns; ++i) {
        for (int j = 0; j < instance.Rows; ++j) {
            int current = instance.RevealedGrid[i][j];

            // check if is a revealed cell
            if (current >= 0 && current <= 8) {
                int bombs = instance.RevealedNeighboringBombs(i, j);
                // check if revealed cell and neighboring bombs match
                if (current != bombs)
                    return false;
            }
        }
    }
    return true;
}

static bool TestAllCombinations(MinesweeperInstance instance, int bombs, int initIndex) {
    if (bombs <= 0) {
        return IsViable(instance);
    }

    int i, j;
    // get next unrevealed cell
    do {
        i = initIndex % instance.Columns;
        j = initIndex / instance.Columns;

        if (!instance.IndexesAreValid(i, j))
            return IsViable(instance);

        initIndex++;
    } while (instance.CellIsRevealed(i, j));


    instance.AddBombAt(i, j);
    if (TestAllCombinations(instance, --bombs, initIndex))
        return true;
    instance.RemoveBombAt(i, j);
    return TestAllCombinations(instance, ++bombs, initIndex);
}

int main() {
    MinesweeperInstance instance = MinesweeperInstance(6, 6);
    instance.PlaceBombsOnTheGrid(3);
    instance.CalculateSolution();
    instance.PrintSolution();
//    instance.RevealAt(0, 0, false);

    MinesweeperBot bot = MinesweeperBot();

    for (int i = 0; i < 15; ++i) {
        int botChoice = bot.ChooseCellToReveal(instance);
        std::cout << "------------------- Chose Cell (" << botChoice % instance.Rows << ", " << botChoice / instance.Rows << ")" << std::endl;
        bool flagBomb = botChoice < 0;
        botChoice = flagBomb ? -botChoice : botChoice;
        int revealed = instance.RevealAt(botChoice % instance.Rows, botChoice / instance.Rows, flagBomb);
        if (revealed == -1 && !flagBomb){
            std::cout << "Bot revealed a bomb" << std::endl;
            break;
        }
        instance.PrintRevealedGrid();

        bool finished = true;
        for (int i = 0; i < instance.Columns; ++i) {
            for (int j = 0; j < instance.Rows; ++j) {
                if (instance.RevealedGrid[i][j] == MinesweeperInstance::UNREVEALED_CELL){
                    finished = false;
                    break;
                }
            }
        }

        if (finished){
            std::cout << "Bot finished the game" << std::endl;
            return 1;
        }
    }

//    instance.AddBombAt(0, 1);
//    instance.AddBombAt(1, 0);
//    instance.AddBombAt(1, 1);
//    instance.RevealAt(0, 1, true);
//
//    instance.PrintRevealedGrid();
//
//    MinesweeperBot bot = MinesweeperBot();
//    int revealed = bot.ChooseCellToReveal(instance);
//    std::cout << "ChosenCell " << revealed << std::endl;
//    bool flagBomb = revealed < 0;
//    revealed = flagBomb ? -revealed : revealed;
//    instance.RevealAt(revealed % instance.Rows, revealed / instance.Rows, flagBomb);
//
//    instance.PrintRevealedGrid();
//
//    revealed = bot.ChooseCellToReveal(instance);
//    std::cout << "ChosenCell " << revealed << std::endl;
//    flagBomb = revealed < 0;
//    revealed = flagBomb ? -revealed : revealed;
//    instance.RevealAt(revealed % instance.Rows, revealed / instance.Rows, flagBomb);
//
//    instance.PrintRevealedGrid();
//
//
//    instance.PrintSolution();

//    int maxBombs = instance.GetMaxBombs();
//    for (int bombs = maxBombs; bombs >= 0; --bombs) {
//        if (TestAllCombinations(instance, bombs, 0)) {
//            std::cout << "The instance is valid" << std::endl;
//            return 0;
//        }
//    }
//
//    std::cout << "The instance is invalid" << std::endl;
    return 0;
}