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

static bool IsViable(int **grid);

int main() {

    // TODO create and populate some instances for testing

    // Example on how to create a test instance
    MinesweeperInstance instance = MinesweeperInstance(4, 4);
//    for (int i = 0; i < instance.Columns; i++) {
//        for (int j = 0; j < instance.Rows; j++) {
//            instance.Grid[i][j] = 0;
//        }
//    }

    //TODO Check if instances satisfy conditions
    if (IsViable(instance.Grid)) {
        std::cout << "The instance is valid" << std::endl;
    } else {
        std::cout << "The instance is invalid" << std::endl;
    }

    return 0;
}


static bool IsViable(int **grid) {
    //TODO implement algorithm here
    return false;
}

