#include <iostream>

struct MinesweeperInstance {
public:
    int **Grid;
    int Rows;
    int Columns;

    // Struct constructor
    MinesweeperInstance(int rows, int columns) : Rows(rows), Columns(columns) {
        //Grid memory allocation
        Grid = new int *[columns];
        for (int i = 0; i < columns; i++) {
            Grid[i] = new int[rows];
        }
    }
};

int main() {
    std::cout << "Hello, World!" << std::endl;

    // Testing basic struct
    MinesweeperInstance test = MinesweeperInstance(4, 4);
    for (int i = 0; i < test.Columns; i++) {
        for (int j = 0; j < test.Rows; j++) {
            test.Grid[i][j] = i + j;
        }
    }

    for (int i = 0; i < test.Columns; i++) {
        for (int j = 0; j < test.Rows; j++) {
            std::cout << test.Grid[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}

