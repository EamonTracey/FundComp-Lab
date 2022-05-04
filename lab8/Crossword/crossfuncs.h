// Eamon Tracey (etracey)
// FundComp Lab 8
//
// crossfuncs.h
//

#include <stdbool.h>
#include <stdio.h>

#define NWMAX 20
#define WLMAX 15

// A "crossword" in this context is any word that
// we want to fit into a "crossword puzzle"
//
// When dir is true, the crossword is horizontal
// Otherwise, it is vertical
//
// The positive x direction of crosswords is defined as
// straight down
//
// The positive y direction of crosswords is defined as
// straight to the right
typedef struct {
	char word[WLMAX + 1];
	bool dir;
	int x;
	int y;
	bool inserted;
} Crossword;

int fcmain(FILE *, FILE *);
int cmain(char[NWMAX][WLMAX + 1], int, FILE *);

bool find_solution(Crossword *, Crossword *[], int size);
bool conflict_exists(Crossword *[], int, int, char[WLMAX + 1], bool, int, int);
void insert_crossword(char[WLMAX][WLMAX], Crossword *);

int is_valid_word(char *);
void strupper(char *);
char *strana(char *);

void init_crosswords_ordered(Crossword *[], char[NWMAX][WLMAX + 1], int);
void init_solution_board(char[WLMAX][WLMAX]);
void create_puzzle_board(char[WLMAX][WLMAX], char[WLMAX][WLMAX]);

void fprint_board(FILE *, char[WLMAX][WLMAX]);
void fprint_clues(FILE *, Crossword *[], int);