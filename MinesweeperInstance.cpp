#include <crtdbg.h>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include "MinesweeperInstance.h"

MinesweeperInstance::MinesweeperInstance(int rows, int columns) : Rows(rows), Columns(columns) {
    //RevealedGrid memory allocation and initialization
    RevealedGrid = new int *[columns];
    _solutionGrid = new int *[columns];
    for (int i = 0; i < columns; ++i) {
        RevealedGrid[i] = new int[rows];
        _solutionGrid[i] = new int[rows];
        for (int j = 0; j < rows; ++j) {
            RevealedGrid[i][j] = UNREVEALED_CELL;
            _solutionGrid[i][j] = UNREVEALED_CELL;
        }
    }
}

void MinesweeperInstance::AddBombAt(int i, int j) {
    _ASSERT_EXPR(IndexesAreValid(i, j), "Invalid indexes.");
    _solutionGrid[i][j] = -1;
    Bombs++;
}

void MinesweeperInstance::RemoveBombAt(int i, int j) {
    _ASSERT_EXPR(IndexesAreValid(i, j), "Invalid indexes.");
    _solutionGrid[i][j] = UNREVEALED_CELL;
}


void MinesweeperInstance::RevealNeighbors(int i, int j) {
    _ASSERT_EXPR(IndexesAreValid(i, j), "Invalid indexes.");

    for (int k = i - 1; k <= i + 1; k++) {
        for (int l = j - 1; l <= j + 1; l++) {
            if (!IndexesAreValid(k, l)) continue;
            if (_solutionGrid[k][l] >= 0) {
                RevealedGrid[k][l] = _solutionGrid[k][l];
            }
            if (_solutionGrid[k][l] == 0) {
                RevealNeighbors(k, l);
            }
        }
    }
}


int MinesweeperInstance::RevealAt(int i, int j, bool flagBomb) {
    _ASSERT_EXPR(IndexesAreValid(i, j), "Invalid indexes.");
    int revealed = RevealedGrid[i][j] = flagBomb ? -1 : _solutionGrid[i][j];
    if (revealed == 0) {
        for (int k = i - 1; k <= i + 1; k++) {
            for (int l = j - 1; l <= j + 1; l++) {
                if (!IndexesAreValid(k, l)) continue;
                if (RevealedGrid[k][l] == UNREVEALED_CELL) {
                    RevealAt(k, l, false);
                }
            }
        }
    }

    return revealed;
}

bool MinesweeperInstance::IndexesAreValid(int i, int j) {
    return i >= 0 && j >= 0 && i < Columns && j < Rows;
}

bool MinesweeperInstance::CellIsRevealed(int i, int j) {
    _ASSERT_EXPR(IndexesAreValid(i, j), "Invalid indexes.");
    return RevealedGrid[i][j] != UNREVEALED_CELL;
}

int MinesweeperInstance::GetMaxBombs() {
    int maxBombs = 0;
    for (int i = 0; i < Columns; ++i) {
        for (int j = 0; j < Rows; ++j) {
            int current = RevealedGrid[i][j];
            if (current >= 0 && current <= 8)
                maxBombs += current;
        }
    }
    return maxBombs;
}

int MinesweeperInstance::RevealedNeighboringBombs(int i, int j) {
    int bombs = 0;
    // iterate over neighboring cells on revealed grid
    for (int k = i - 1; k <= i + 1; k++) {
        for (int l = j - 1; l <= j + 1; l++) {
            if (!IndexesAreValid(k, l)) continue;
            if (RevealedGrid[k][l] < 0) bombs++;
        }
    }
    return bombs;
}

int MinesweeperInstance::UnrevealedNeighbors(int i, int j) {
    int count = 0;

    // iterate over neighboring cells on revealed grid
    for (int k = i - 1; k <= i + 1; k++) {
        for (int l = j - 1; l <= j + 1; l++) {
            if (!IndexesAreValid(k, l)) continue;
            if (RevealedGrid[k][l] == UNREVEALED_CELL) count++;
        }
    }
    return count;
}

void MinesweeperInstance::PrintRevealedGrid() {
    for (int i = 0; i < Columns; ++i) {
        for (int j = 0; j < Rows; ++j) {
            if (RevealedGrid[i][j] < UNREVEALED_CELL && RevealedGrid[i][j] >= 0) {
                std::cout << " ";
            }
            std::cout << RevealedGrid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void MinesweeperInstance::PrintSolution() {
    for (int i = 0; i < Columns; ++i) {
        for (int j = 0; j < Rows; ++j) {
            if (_solutionGrid[i][j] >= 0) {
                std::cout << " ";
            }
            std::cout << _solutionGrid[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void MinesweeperInstance::PlaceBombsOnTheGrid(int bombs) {
    _ASSERT_EXPR(bombs < Columns * Rows, "Number of bombs greater or equal to the number of cells");

    Bombs += bombs;
    srand((unsigned) time(nullptr));
    while (bombs > 0) {
        int random = rand() % (Columns * Rows);
        if (_solutionGrid[random / Rows][random % Rows] != -1) {
            _solutionGrid[random / Rows][random % Rows] = -1;
            bombs--;
        }
    }
}

int MinesweeperInstance::NeighboringBombs(int i, int j) {
    int bombs = 0;
    // iterate over neighboring cells
    for (int k = i - 1; k <= i + 1; k++) {
        for (int l = j - 1; l <= j + 1; l++) {
            if (!IndexesAreValid(k, l)) continue;
            if (_solutionGrid[k][l] < 0) bombs++;
        }
    }
    return bombs;
}

void MinesweeperInstance::CalculateSolution() {
    for (int i = 0; i < Columns; ++i) {
        for (int j = 0; j < Rows; ++j) {
            if (_solutionGrid[i][j] >= 0)
                _solutionGrid[i][j] = NeighboringBombs(i, j);
        }
    }
}

MinesweeperInstance MinesweeperInstance::CopyFromRevealedGrid() {
    MinesweeperInstance instance = MinesweeperInstance(Rows, Columns);
    for (int i = 0; i < Columns; ++i) {
        for (int j = 0; j < Rows; ++j) {
            instance.RevealedGrid[i][j] = RevealedGrid[i][j];
        }
    }
    return instance;
}
