// Author: Liam Biddle - z5311885
// Date: 12 - 07 - 2020
// UNSW Freefall assignment.
// Freefall is a vertical shooter arcade  game similar to Space Invaders 
// and Galaga. You, the playe must defend the player from the falling
// stones with a laser. To start you have to input the rows of stones. Then
// you must move the player and fire the laser to destroy all the stones

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 15
//value in array
#define EMPTY 0
#define STONE 1

//command defines
#define MOVE_PLAYER 1
#define LASER 2
#define SHIFT_DOWN 3
#define VERT_FLIP 4

//game end condition defines 
#define GAME_CONTINUE 0
#define GAME_LOSE 1
#define GAME_WIN 2

void printMap(int map[SIZE][SIZE], int playerX);
void placeStone(int numLines, int map[SIZE][SIZE]);
int movePlayer (int playerX);
void fireLaser (int map[SIZE][SIZE], int playerX);
void shiftDown (int map[SIZE][SIZE]);
int endCondition(int map[SIZE][SIZE]);
void vertFlip(int map[SIZE][SIZE]);
void swapNums(int map[SIZE][SIZE], int row, int col);
void tntBlocks(int map[SIZE][SIZE],int row, int col, int radius);

int main (void) {
    
    int map[SIZE][SIZE] = {EMPTY};
    int playerX = SIZE / 2;

    printf("How many lines of stone? ");
    int numLines;
    // scans number of lines in int numLines
    scanf("%d", &numLines); 

    printf("Enter lines of stone:\n");
    // this function places amount of stones
    placeStone(numLines, map); 
    printMap(map, playerX);
    // variable for end condition for EOF loop for the commands 
    // vertCount is the counter for the command VERT_FLIP 
    // as it can only be run once
    int vertCount = 0;
    // int end is the ending variable for if the EOF is input, 
    // end is changed to -1, ending the command input loop

    int end = 1; 
	// command input loop
	while (end == 1) {
	    int command;
	    //setting end, to check for an EOF
	    end = scanf("%d", &command);
	    if (end == 1) {
	    	// if command to move the player is input, this runs the player move function
	        if (command == MOVE_PLAYER) { 
	            playerX = movePlayer(playerX); 
	            printMap(map, playerX);
	        }
			// if VERT_FLIP command is input, it runs the flip function. While it can only run once
	        if (command == VERT_FLIP) {
	        	if (vertCount <= 0) {
	        		vertFlip(map);
	        		vertCount++;
	        	}
	        	printMap(map, playerX);
        	}

	        if (command == LASER || command == SHIFT_DOWN) {
	        	int end_condition = endCondition(map);
		        // if fireLaser command is input, runs fireLaser function is run
		        if (command == LASER) { 
		            fireLaser(map, playerX);
		            printMap(map, playerX);
		            // if the laser is fired, and no STONES
		            if (endCondition(map) == GAME_WIN) {
		            	printf("Game Won!\n");
		        		end = -1;
		            }
		        }
		        else if (command == SHIFT_DOWN && end_condition == GAME_CONTINUE) { 
		        // if shift down is input, the array is shifted down
		        	shiftDown(map);
		        	printMap(map, playerX);
		        }
		        else if (end_condition == GAME_LOSE) {
		        	printMap(map,playerX);
		        	printf("Game Lost!\n");
		        	end = -1;
		        }
	        }
        }
	}	
    return 0;
}

// Print out the contents of the map array. Then print out the player line
// which will depends on the playerX variable.
void printMap(int map[SIZE][SIZE], int playerX) {
    
    // Print values from the map array.
    int i = 0;
    while (i < SIZE) {
        int j = 0;
        while (j < SIZE) {
            printf("%d ", map[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }    
    
    // Print the player line.
    i = 0;
    while (i < playerX) {
        printf("  ");
        i++;
    }
    printf("P\n");
}
// this void function is used for inputing the lines of STONE into the array
void placeStone(int numLines, int map[SIZE][SIZE]) {
	// counter for loop of Lines   
    int lineCounter = 0; 
    while (lineCounter < numLines) {
        int row, column, length, value;
        scanf("%d %d %d %d", &row, &column, &length, &value);
        int coLength = column + length;
        // if condition so that invalid inputs are rejected 
        if (
        	row > SIZE || row < 0 || column < 0 || column > SIZE || 
        	coLength > SIZE) {}
        else {
            int colCount = column;
            while (colCount < coLength) {
                map[row][colCount] = value;
                colCount++;
            }
         }
    lineCounter++;
    }
}
// this integer function is used to change the player's position, it returns
// the playerX variable which determines the player's position
int movePlayer (int playerX) {
    int direction;
    scanf("%d", &direction);
    if (direction == 1) { 
    // input of 1 means the P moves to the right
        playerX++;
    }
    else if (direction == -1) { 
    // input of -1 means the P moves to the left 
        playerX--;
    }
    return playerX;
}
// this void function fires the player's laser destroying max of 3 stones, or 
// destroying a TNT block
void fireLaser (int map[SIZE][SIZE], int playerX) {
    int loopCounter = SIZE - 1;
    int destroyCount = 0;
    // loop for bottom to top values of the array, while also accounts for 
    // how many stones have been destroyed. 
    while (destroyCount < 3 && loopCounter >= 0) {
        if (map[loopCounter][playerX] == STONE) {
            map[loopCounter][playerX] = EMPTY;
            destroyCount++;
        }
        else if(map[loopCounter][playerX] >= 3 && 
    	map[loopCounter][playerX] <= 9) {
        	
        	tntBlocks(map,loopCounter,playerX,map[loopCounter][playerX]);
        	destroyCount = 3;
        }
        // another if statement will have to be added later in Stage 3 for 
        // TNT blocks referncing another function
        loopCounter--;
    }
} 
// this void function shifts the whole games array down a row
void shiftDown (int map[SIZE][SIZE]) {
	int colCount = 0;
	while (colCount < SIZE) {
		int rowCount = SIZE -1;
		while (rowCount > 0) {
			map[rowCount][colCount] = map[rowCount - 1][colCount];
			rowCount--;
		}
		map[0][colCount] = EMPTY;
		colCount++;
	}
}
// this integer function is used for calculating if the end conditions 
// have been met, it return either a GAME_LOSE, GAME_WIN or GAME_CONTINUE value
// depending if the game has been won or lost
int endCondition(int map[SIZE][SIZE]) {
	int rowCount = 0;
	int countWin = 0;
	// loops looks for STONE values, if found adds value of STONE to countWin, 
	// then if it returns 0, then Game must be won
	while (rowCount < SIZE) { 
		int colCount = 0;
		while (colCount < SIZE) {
			countWin = countWin + map[rowCount][colCount];
			colCount++;
		}
		rowCount++;
	}
	int colCount2 = 0;	
	int countLose = 0;
	// counts final row and checks for STONE, if STONE is found, then adds 
	// to counter
	while (colCount2 < SIZE) { 
		if (map[14][colCount2] > 0) {
			countLose++;	
		}
		colCount2++;
	}
	if (countLose > 0) { 
	// if there is a STONE in the bottom row then GAME_LOSE is given
		return GAME_LOSE;	
	}
	else if (countWin == 0) {
		return GAME_WIN; 
		// returns GAME win
	}
	else { 
	// if GAME is neither lost or won, GAME_CONTINUE is given 
		return GAME_CONTINUE;
	}
}

// this void function vertically flips the array
void vertFlip(int map[SIZE][SIZE]) {
	int colCount = 0;
	while (colCount < SIZE) {
		int rowCount = 0;
		while (rowCount < 7) {
			swapNums(map,rowCount,colCount);
			rowCount++;
		}
		colCount++;
	}
}

// this void function is used for swapping two numbers vertically
void swapNums(int map[SIZE][SIZE], int row, int col) {
	int temp = map[row][col];
	int newRow = SIZE - 1 - row;
	map[row][col] = map[newRow][col];
	map[newRow][col] = temp;
}
// this void function replaces the values in the TNT radius to EMPTY
void tntBlocks(int map[SIZE][SIZE],int row, int col, int radius) {
	int rowCount = 0;
	while (rowCount < SIZE) {
		int colCount = 0;
		while (colCount < SIZE) {
			int radColumn = pow(colCount - col,2);
			int radRow = pow(rowCount - row,2);
			double radiusCheck = sqrt(radColumn + radRow);
			// this if statement is used to check every value in the array is
			// in the radius, and if so the value is changed to 0
			if (radiusCheck < radius) {
				map[rowCount][colCount] = EMPTY;
			}
			colCount++;
		}
		rowCount++;
	}
}

