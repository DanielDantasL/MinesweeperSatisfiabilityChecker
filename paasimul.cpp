#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#define COLUMNS 6
#define ROWS 6


/** Values 0 to 8 are represent how many bombs there are on the vicinity
 *  of the tile.
 *  
 *  Value 9 represent an unkown tile, whether it has a bomb or is an empty
 *  tile.
 *  Value 9 is read as a bomb during the "checking"
**/


// Print the Grid.
void printGrid(int grid[ROWS][COLUMNS]){

    for(int i=0; i<ROWS ; i++){
        for(int j=0; j<COLUMNS ; j++){
            printf("[%d]", grid[i][j]);
        }
        printf("\n");
    }
}
// End


// Checking adjacent tiles.

    // Superior Left Diagonal.
    inline void check1(int grid[][COLUMNS], int i, int j){
        if(i-1 >= 0 && j-1 >= 0)
            if(grid[i-1][j-1] == 9){
                grid[i][j] +=1;
            }
    }
    // Superior Middle.
    inline void check2(int grid[][COLUMNS], int i, int j){
        if(i-1 >= 0){
            if(grid[i-1][j] == 9){
                grid[i][j] +=1;
            }
        }
    }
    // Superior Right Diagonal.
    inline void check3(int grid[][COLUMNS], int i, int j){
        if(i-1 >= 0 && j+1 < COLUMNS){
            if(grid[i-1][j+1] == 9){
                grid[i][j] +=1;
            }
        }
    }
    // Middle Left.
    inline void check4(int grid[][COLUMNS], int i, int j){
        if(j-1 >= 0){
            if(grid[i][j-1] == 9){
                grid[i][j] +=1;
            }
        }
    }
    // Middle Right.
    inline void check5(int grid[][COLUMNS], int i, int j){
        if(j+1 < COLUMNS){
            if(grid[i][j+1] == 9){
                grid[i][j] +=1;
            }
        }
    }
    // Inferior Left Diagonal.
    inline void check6(int grid[][COLUMNS], int i, int j){
        if(i+1 < ROWS && j-1 >= 0){
            if(grid[i+1][j-1] == 9){
                grid[i][j] +=1;
            }
        }
    }
    // Inferior Middle.
    inline void check7(int grid[][COLUMNS], int i, int j){
        if(i+1 < ROWS){
            if(grid[i+1][j] == 9){
                grid[i][j] +=1;
            }
        }
    }
    // Inferior Right Diagonal.
    inline void check8(int grid[][COLUMNS], int i, int j){
        if(i+1 < ROWS && j-1 < COLUMNS){
            if(grid[i+1][j+1] == 9){
                grid[i][j] +=1;
            }
        }
    }

// End.


void CheckAdjacencies(int grid[][COLUMNS]){
    for(int i=0; i<ROWS ; i++){
        for(int j=0; j<COLUMNS ; j++){

            if(grid[i][j] == 9){
                continue;
            }

            check1(grid, i, j);
            check2(grid, i, j);
            check3(grid, i, j);
            check4(grid, i, j);
            check5(grid, i, j);
            check6(grid, i, j);
            check7(grid, i, j);
            check8(grid, i, j);


        }
    }
}


// Initializing grid with unknow tiles.

void turnedTiles(int grid[][COLUMNS]){
    
    for(int j=0 ; j<COLUMNS ; j++){
        grid[0][j] = 9;
    }

    for(int i=0 ; i<ROWS ; i++){
        grid[i][0] = 9;
    }

    for(int i=0 ; i<ROWS ; i++){
        grid[i][COLUMNS-1] = 9;
    }

    for(int j=0 ; j<COLUMNS ; j++){
        grid[ROWS-1][j] = 9;
    }
}

// End.


// Setting up the enviroment.

void enviroment(int grid[][COLUMNS]){

    grid[0][3] = 9;
    grid[0][2] = 9;
    grid[5][3] = 9;

    CheckAdjacencies(grid);


    // Use this space to arbitralily choose other unkown values(9).

    turnedTiles(grid);

    // End.

    printGrid(grid);
    
}

// End.


int main(){

    int grid[ROWS][COLUMNS] = {0};

    enviroment(grid);




    return 0;
}