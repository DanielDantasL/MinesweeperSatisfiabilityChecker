#ifndef MINESWEEPERSATISFIABILITYCHECKER_MINESWEEPERINSTANCE_H
#define MINESWEEPERSATISFIABILITYCHECKER_MINESWEEPERINSTANCE_H

class MinesweeperInstance {
public:
    MinesweeperInstance(int rows, int columns);

    static const int UNREVEALED_CELL = 88;
    int **RevealedGrid;
    int Rows;
    int Columns;
    int Bombs;

    void AddBombAt(int i, int j);

    void PlaceBombsOnTheGrid(int bombs);

    void CalculateSolution();

    void RemoveBombAt(int i, int j);

    int RevealAt(int i, int j, bool flagBomb);

    void RevealNeighbors(int i, int j);

    bool IndexesAreValid(int i, int j);

    bool CellIsRevealed(int i, int j);

    int GetMaxBombs();

    int RevealedNeighboringBombs(int i, int j);

    int UnrevealedNeighbors(int i, int j);

    void PrintRevealedGrid();

    void PrintSolution();

    MinesweeperInstance CopyFromRevealedGrid();

private:
    int **_solutionGrid;

    int NeighboringBombs(int i, int j);

};


#endif //MINESWEEPERSATISFIABILITYCHECKER_MINESWEEPERINSTANCE_H
