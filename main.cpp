#include <iostream>

struct MinesweeperInstance {
public:
    int **Grid;
    int Rows;
    int Columns;
    void AddBombAt(int i, int j);
    void RemoveBombAt(int i, int j);
    void RevealAt(int i, int j, int value);
    bool IndexesAreValid(int i, int j);
    bool CellIsRevealed(int i, int j);
    int GetMaxBombs();
    int HasNeighboringBombs(int i, int j);

    // Struct constructor
    MinesweeperInstance(int rows, int columns) : Rows(rows), Columns(columns) {
        //Grid memory allocation and initialization
        Grid = new int *[columns];
        for (int i = 0; i < columns; ++i) {
            Grid[i] = new int[rows];
            for (int j = 0; j < rows; ++j) {
                // initialize all grid cells with 88 (unrevealed cells)
                Grid[i][j] = 88;
            }
        }
    }

};

void MinesweeperInstance::AddBombAt(int i, int j) {
    // check if indexes are invalid
    if (!IndexesAreValid(i, j))
        return;

    // bombs are represented by any number less than 0
    Grid[i][j] = -1;
}

void MinesweeperInstance::RemoveBombAt(int i, int j) {
    // check if indexes are invalid
    if (!IndexesAreValid(i, j))
        return;

    // removed bombs are replaced with unrevealed cells
    Grid[i][j] = 88;
}

int MinesweeperInstance::HasNeighboringBombs(int i, int j) {
    int bombs = 0;
    // iterate over neighboring cells
    for (int k = i - 1; k <= i + 1 ; k++) {
        for (int l = j - 1; l <= j + 1; l++) {
            // check if indexes are invalid
            if (!IndexesAreValid(k, l))
                continue;
            // check if cell has a bomb
            if (Grid[k][l] < 0)
                bombs++;
        }
    }
    return bombs;
}

void MinesweeperInstance::RevealAt(int i, int j, int value) {
    // revealed value cannot be < 0 or > 8 and indexes must be valid
    if (value < 0 || value > 8 || !IndexesAreValid(i, j))
        return;

    Grid[i][j] = value;
}

bool MinesweeperInstance::IndexesAreValid(int i, int j) {
    return i >= 0 && j >= 0 && i < Columns && j < Rows;
}

bool MinesweeperInstance::CellIsRevealed(int i, int j) {
    if (!IndexesAreValid(i, j))
        return false;

    return Grid[i][j] >= 0 && Grid[i][j] <= 8;
}

int MinesweeperInstance::GetMaxBombs() {
    int maxBombs = 0;
    for (int i = 0; i < Columns; ++i) {
        for (int j = 0; j < Rows; ++j) {
            int current = Grid[i][j];
            if (current >= 0 && current <= 8)
                maxBombs += current;
        }
    }
    return maxBombs;
}

static bool IsViable(MinesweeperInstance instance) {
    for (int i = 0; i < instance.Columns; ++i) {
        for (int j = 0; j < instance.Rows; ++j) {
            int current = instance.Grid[i][j];

            // check if is a revealed cell
            if (current >= 0 && current <= 8) {
                int bombs = instance.HasNeighboringBombs(i, j);
                // check if revealed cell and neighboring bombs match
                if (current != bombs)
                    return false;
            }
        }
    }
    return true;
}

static bool TestAllCombinations(MinesweeperInstance instance, int bombs, int initIndex){
    if (bombs <= 0){
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
    MinesweeperInstance instance = MinesweeperInstance(4, 4);
    instance.RevealAt(0, 0, 3);
    instance.RevealAt(1, 3, 5);

    if (TestAllCombinations(instance, instance.GetMaxBombs(), 0)) {
        std::cout << "The instance is valid" << std::endl;
    } else {
        std::cout << "The instance is invalid" << std::endl;
    }

    return 0;
}