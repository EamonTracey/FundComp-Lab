// Eamon Tracey (etracey)
// FundComp Lab 6 lifefunc.c
//
// Game of Life implementation on 40x40 grid
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lifefunc.h"

const int SIZE = 40;
const int LCHAR = 'x';

// Play Conway's Game of Life interactively
void play_interactive() {
	char option, game_board[SIZE][SIZE];
	int opx, opy, play = 1;

	// Initialize board and display
	initialize_board(game_board);
	update_display(game_board);
	
	while (play) {
		printf("Option: ");
		scanf(" %c", &option);

		// Handle user option
		switch (option) {
			case 'a':
				scanf("%d %d", &opx, &opy);
				if (opx < 0 || opx >= SIZE || opy < 0 || opy >= SIZE) {
					printf("ERROR: Invalid coordinate (must be [0, 39])\n");
				} else {
					liven_cell(game_board, opx, opy);
					update_display(game_board);
				}
				break;
			case 'r':
				scanf("%d %d", &opx, &opy);
				if (opx < 0 || opx >= SIZE || opy < 0 || opy >= SIZE) {
					printf("ERROR: Invalid coordinate (must be [0, 39])\n");
				} else {
					kill_cell(game_board, opx, opy);
					update_display(game_board);
				}
				break;
			case 'n':
				advance_game(game_board);
				update_display(game_board);
				break;
			case 'q':
				play = 0;
				break;
			case 'p':
				play_forever(game_board);
				break;
			default:
				printf("Invalid option\n");
		}
	}

	clear();
	printf("Exited Game of Life\n");
}

// Play Conway's Game of Life with a file of commands
void play_batch(char filepath[]) {
	FILE *fp;
	char line[9], option, game_board[SIZE][SIZE];
	int opx, opy, play = 1;

	// Open and verify file
	fp = fopen(filepath, "r");
	if (!fp) {
		printf("ERROR: File %s does not exist\n", filepath);
		return;
	}

	// Initialize board
	initialize_board(game_board);

	while (fgets(line, 8, fp)) { // Maximum command length 8
		// Handle line option
		switch (line[0]) {
			printf("%c", line[0]);
			case 'a':
				sscanf(line, "%*c %d %d", &opx, &opy);
				liven_cell(game_board, opx, opy);
				break;
			case 'r':
				sscanf(line, "%*c %d %d", &opx, &opy);
				kill_cell(game_board, opx, opy);
				break;
			case 'p':
				update_display(game_board);
				play_forever(game_board);
				break;
		}
	}
}

// Initialize SIZE*SIZE board with dead cells
void initialize_board(char board[][SIZE]) {
	int i, j;
	for (i = 0; i < SIZE; ++i) {
		for (j = 0; j < SIZE; ++j) {
			board[i][j] = ' ';
		}
	}
}

// Liven cell at given coordinate
void liven_cell(char board[][SIZE], int x, int y) {
	board[x][y] = LCHAR;
}

// Kill cell at given coordinate
void kill_cell(char board[][SIZE], int x, int y) {
	board[x][y] = ' ';
}

// Copy 2D char array to 2D char array
void copy_board(char destination[][SIZE], char source[][SIZE]) {
	int i, j;
	for (i = 0; i < SIZE; ++i) {
		for (j = 0; j < SIZE; ++j) {
			destination[i][j] = source[i][j]; // Copy every element
		}
	}
}

// Clear display and print board
void update_display(char board[][SIZE]) {
	int SIZE_m1 = SIZE - 1;

	clear(); // Clear display
	printf("Game of Life\n\n"); // Print title

	int i, j;	
	
	printf(" ");
	for (i = 0; i < SIZE; ++i) { // Print grid top
		printf("–");
	}
	printf("\n");

	for (i = 0; i < SIZE; ++i) { // Print filled grid
		for (j = 0; j < SIZE; ++j) {
			if (j == 0) printf("|");
			printf("%c", board[i][j]); // Display cell
			if (j == SIZE_m1) printf("|");
		}
		printf("\n");
	}

	printf(" ");
	for (i = 0; i < SIZE; ++i) { // Print grid bottom
		printf("–");
	}
	printf("\n");
}

// Apply rules of game to board
void advance_game(char board[][SIZE]) {
	char iboard[SIZE][SIZE];

	copy_board(iboard, board);

	int i, j, neighbors;
	for (i = 0; i < SIZE; ++i) {
		for (j = 0; j < SIZE; ++j) {
			neighbors = number_neighbors(iboard, i, j);
			if (iboard[i][j] == LCHAR) { // Alive cell
				if (!(neighbors == 2 || neighbors == 3)) { // Not 2 or 3 neighbors
					kill_cell(board, i, j); // Cell dies
				} // else cell survives
			} else { // Dead cell
				if (neighbors == 3) { // 3 neighbors
					liven_cell(board, i, j);
				} // else cell remains dead
			}
		}
	}
}

// Count number of neighbors of given coordinate on board
int number_neighbors(char board[][SIZE], int x, int y) {
	// Define x positive direction as down, y positive direction as right (on Cartesian plane)

	int x_min, x_max, y_min, y_max, neighbors = 0, SIZE_m1 = SIZE - 1;

	// Compute x and y minimum and maximum values that encapsulate potentially alive neighbors
	x_min = x == 0 ? x : x - 1;
	x_max = x == SIZE_m1 ? x : x + 1;
	y_min = y == 0 ? y : y - 1;
	y_max = y == SIZE_m1 ? y : y + 1;
	
	int i, j;
	for (i = x_min; i <= x_max; ++i) {
		for (j = y_min; j <= y_max; ++j) {
			if (i == x && j == y) continue; // Skip cell itself
			if (board[i][j] == LCHAR) ++neighbors; // Alive neighbor found -> increment
		}
	}

	return neighbors;
}

// Continuously play game
void play_forever(char board[][SIZE]) {
	while (1) {
		advance_game(board);
		update_display(board);
		usleep(200000); // 0.2 seconds
	}
}


// Clear screen
void clear() {
	system("clear");
}
