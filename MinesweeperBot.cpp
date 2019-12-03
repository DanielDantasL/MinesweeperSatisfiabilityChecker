#include <iostream>
#include "MinesweeperBot.h"

int MinesweeperBot::ChooseCellToReveal(MinesweeperInstance instance) {
    // iterate through all grid cells
    int unrevealed = 0;
    for (int i = 0; i < instance.Columns; ++i) {
        for (int j = 0; j < instance.Rows; ++j) {
            int current = instance.RevealedGrid[i][j];
            if (current == MinesweeperInstance::UNREVEALED_CELL) {
                unrevealed++;
                continue;
            } else if (current >= 1 && current <= 8) {
                int neighboringBombs = instance.RevealedNeighboringBombs(i, j);
                int unrevealedNeighbors = instance.UnrevealedNeighbors(i, j);

                if (neighboringBombs == current && unrevealedNeighbors > 0) {
                    for (int k = i - 1; k <= i + 1; k++) {
                        for (int l = j - 1; l <= j + 1; l++) {
                            if (!instance.IndexesAreValid(k, l) ||
                                instance.RevealedGrid[k][l] != MinesweeperInstance::UNREVEALED_CELL)
                                continue;
                            // choose unrevealed space
                            return l * instance.Rows + k;
                        }
                    }
                }

                if (neighboringBombs + unrevealedNeighbors == current) {
                    for (int k = i - 1; k <= i + 1; k++) {
                        for (int l = j - 1; l <= j + 1; l++) {
                            if (!instance.IndexesAreValid(k, l) ||
                                instance.RevealedGrid[k][l] != MinesweeperInstance::UNREVEALED_CELL)
                                continue;
                            // choose unrevealed space (negative to signalize that it is marking a bomb)
                            return -(l * instance.Rows + k);
                        }
                    }
                }
            }
        }
    }

    // Grid is completely unrevealed
    if (unrevealed == instance.Rows * instance.Columns) {
        // choose blindly
        return 0;
    }

    // heuristic
    int maxScore = INT32_MIN, maxScore_i = 0, maxScore_j = 0;
    for (int i = 0; i < instance.Columns; ++i) {
        for (int j = 0; j < instance.Rows; ++j) {
            int current = instance.RevealedGrid[i][j];
            if (current != MinesweeperInstance::UNREVEALED_CELL) continue;

            MinesweeperInstance dummy = instance.CopyFromRevealedGrid();
            dummy.RevealAt(i, j, true);
            int score = CalculateInstanceScore(dummy);
            if (score > maxScore) {
                maxScore = score;
                maxScore_i = i;
                maxScore_j = j;
            }
        }
    }

    return -(maxScore_j * instance.Rows + maxScore_i);
}

int MinesweeperBot::CalculateInstanceScore(MinesweeperInstance instance) {
    int minInstanceScore = INT32_MAX;
    int roundScore = INT32_MAX - 1;
    while (roundScore < minInstanceScore) {
        minInstanceScore = roundScore;
        roundScore = 0;
        for (int i = 0; i < instance.Columns; ++i) {
            for (int j = 0; j < instance.Rows; ++j) {
                int current = instance.RevealedGrid[i][j];
                if (current < 0 || current > 8) continue;

                int cellScore = instance.RevealedNeighboringBombs(i, j) - current;
                for (int k = i - 1; k <= i + 1; k++) {
                    for (int l = j - 1; l <= j + 1; l++) {
                        if (!instance.IndexesAreValid(k, l) || instance.RevealedGrid[k][l] <= 8) continue;
                        instance.RevealedGrid[k][l] -= cellScore;
                    }
                }
                roundScore += cellScore;
            }
        }

        // reset unrevealed scores
        int maxUnrevealedScore = INT32_MIN;
        int maxUnrevealedScore_i = -1;
        int maxUnrevealedScore_j = -1;

        for (int i = 0; i < instance.Columns; ++i) {
            for (int j = 0; j < instance.Rows; ++j) {
                int current = instance.RevealedGrid[i][j];
                if (current <= 8) continue;

                if (instance.RevealedGrid[i][j] > maxUnrevealedScore){
                    maxUnrevealedScore = instance.RevealedGrid[i][j];
                    maxUnrevealedScore_i = i;
                    maxUnrevealedScore_j = j;
                }
                instance.RevealedGrid[i][j] = MinesweeperInstance::UNREVEALED_CELL;
            }
        }

        instance.AddBombAt(maxUnrevealedScore_i, maxUnrevealedScore_j);
    }

    return minInstanceScore;
}
