// Eamon Tracey (etracey)
// FundComp Lab 8
//
// crossfuncs.c
//
// Note to grader: Both extra credits were implemented
//

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "crossfuncs.h"

#define NWMAX 20
#define WLMAX 15

#define ERR_MSG_1_WORD "ERROR: Must enter at least 1 word\n"
#define ERR_MSG_2_CHAR "ERROR: Word must have at least 2 characters (\"%s\" ignored)\n"
#define ERR_MSG_WLMAX_CHAR "ERROR: Word must have at most %d characters (\"%s\" ignored)\n"
#define ERR_MSG_ALPHA_CHAR "ERROR: Word must contain only alpha characters (\"%s\" ignored)\n"
#define CLUES_HEADER "Position | Type   | Clue\n–––––––––*––––––––*––––––––––––––––\n"

// Main function to parse user input
int fcmain(FILE *infp, FILE *outfp) {
	char words[NWMAX][WLMAX + 1], word[256];
	int nwords = 0;

	if (infp == stdin) printf("Enter words (\".\" to end input):\n");

	while (nwords < NWMAX) {
		if (infp == stdin) printf("Word %d: ", nwords + 1);
		
		fgets(word, 256, infp);
		word[strlen(word) - 1] = '\0';

		if (!strcmp(word, ".")) {
			if (nwords) {
				break;
			} else {
				fprintf(outfp, ERR_MSG_1_WORD);
				if (infp == stdin) continue; else return -1;
			}
		}

		switch (is_valid_word(word)) {
			case 1:
				fprintf(outfp, ERR_MSG_2_CHAR, word);
				break;
			case 2:
				fprintf(outfp, ERR_MSG_WLMAX_CHAR, WLMAX, word);
				break;
			case 3:
				fprintf(outfp, ERR_MSG_ALPHA_CHAR, word);
				break;
			default:
				strupper(word);
				strcpy(words[nwords++], word);
		}
	}

	return cmain(words, nwords, outfp); 
}

// All-encompassing crossword main function that handles parsed word array
int cmain(char words[NWMAX][WLMAX + 1], int size, FILE *outfp) {
	int i;

	char solution_board[WLMAX][WLMAX];
	char puzzle_board[WLMAX][WLMAX];

	Crossword *crosswords[size];

	bool try = true;

	// Initialize crosswords array
	init_crosswords_ordered(crosswords, words, size);

	// Initialize solution board
	init_solution_board(solution_board);

	// Insert first (longest word) into middle, horizontally
	crosswords[0]->dir = true;
	crosswords[0]->x = WLMAX / 2;
	crosswords[0]->y = (WLMAX - strlen(crosswords[0]->word)) / 2;
	insert_crossword(solution_board, crosswords[0]);

	fprintf(outfp, "\nAttempts:\n");
	fprintf(outfp, "Inserted %s\n", crosswords[0]->word);

	// Generate solution
	while (try) {
		try = false;

		for (i = 1; i < size; ++i) {
			// Skip already inserted crosswords
			if (crosswords[i]->inserted) continue;

			if (find_solution(crosswords[i], crosswords, size)) {
				// Solution was found, so insert crossword
				insert_crossword(solution_board, crosswords[i]);

				// If a new crossword is inserted, we should go back through
				// uninserted crosswords and check if they are now insertable
				try = true;

				fprintf(outfp, "Inserted %s\n", crosswords[i]->word);
			} else {
				fprintf(outfp, "Skipped %s\n", crosswords[i]->word);
			}
		}
	}

	// Initialize puzzle board from solution board
	create_puzzle_board(puzzle_board, solution_board);

	// Print solution, puzzle, and clues
	fprintf(outfp, "\nCrossword Solution:\n");
	fprint_board(outfp, solution_board);
	fprintf(outfp, "\nCrossword Puzzle:\n");
	fprint_board(outfp, puzzle_board);
	fprintf(outfp, "\nClues:\n");
	fprint_clues(outfp, crosswords, size);

	// Close output file
	fclose(outfp);

	// Deallocate crosswords
	for (i = 0; i < size; ++i) {
		free(crosswords[i]);
	}

	return 0;
}

// Find valid position to insert a crossword given all
// other crosswords
bool find_solution(Crossword *cw, Crossword *cws[], int size) {
	int i, j, k;

	int length = strlen(cw->word);

	Crossword *icwoi;
	int icwoi_length;

	bool pdir;
	int px;
	int py;

	bool conflict;

	Crossword *icws[size];
	int nicws = 0;

	// Collect inserted crosswords because
	// that is all we care about
	for (i = 0; i < size; ++i) {
		if (cws[i]->inserted) {
			icws[nicws++] = cws[i];
		}
	}

	// Loop through inserted words
	for (i = 0; i < nicws; ++i) {
		// icwoi ~ inserted crossword of interest
		icwoi = icws[i];
		icwoi_length = strlen(icwoi->word);

		// Loop through characters of word to insert
		for (j = 0; j < length; ++j) {
			// Loop through characters of icwoi
			for (k = 0; k < icwoi_length; ++k) {
				if (cw->word[j] == icwoi->word[k]) {
					// Character match found
					//
					// Now check if this potential insertion causes
					// problems with the rest of the board
					//
					// The crossword must have the different direction
					// of the word it intersects
					pdir = !icwoi->dir;

					if (pdir) {
						// Horizontal insertion means x lies at the x position
						// of the word to intersect plus the index of the 
						// character to intersect and y lies at the y position
						// of the character to intersect minus the index of the
						// character with which we want to intersect
						px = icwoi->x + k;
						py = icwoi->y - j;
					} else {
						// Vertical insertion position computation is the
						// inverse of the horizontal computation
						px = icwoi->x - j;
						py = icwoi->y + k;
					}

					// Check for conflict with existing board
					conflict = conflict_exists(icws, nicws, i, cw->word, pdir, px, py);

					if (conflict) {
						// Conflict detected, so try to find another match
						conflict = false;
						continue;
					}
					
					// Success!
					// Assign solution to the crossword
					cw->dir = pdir;
					cw->x = px;
					cw->y = py;

					return true;
				}
			}
		}
	}

	// After exhausting all potential character matches,
	// finding that each one had a conflict, there exists
	// no solution with the given board
	return false;
}

// WHAT THE F*CK
//
// Check if there is a conflict placing a new word at some position
// given all previously inserted crosswords and the
// particular crossword to be intersected
bool conflict_exists(Crossword *cws[], int size, int icwoii, char word[WLMAX + 1], bool dir, int x, int y) {
	int i, j;

	int reserved_x[WLMAX * WLMAX];
	int reserved_y[WLMAX * WLMAX];
	int nr = 0;

	int ch_x, ch_y;

	int length = strlen(word);

	// Position falls outside WLMAX * WLMAX box -> conflict
	//
	// Note the attempted position can only be to the left or above
	// the box, so we only check for negative x and y values
	if (x < 0 || y < 0) return true;

	// Collect reserved coordinates
	//
	// A coordinate is reserved if it is in use by any crossword
	// EXCEPT the crossword that we want to intersect
	//
	// It is already known that there is no conflict with the
	// crossword to be intersected, so no check is necessary
	for (i = 0; i < size; ++i) {
		for (j = 0; j < strlen(cws[i]->word); ++j) {
			if (i != icwoii) {
				// Horizontal crosswords vary on y
				// Vertical crosswords vary on x
				reserved_x[nr] = cws[i]->dir ? cws[i]->x : cws[i]->x + j;
				reserved_y[nr++] = cws[i]->dir ? cws[i]->y + j : cws[i]->y;
			}
		}
	}

	// For each character, four special coordinates must be checked:
	// 1) Coordinate above
	// 2) Coordinate below
	// 3) Coordinate to the left
	// 4) Coordinate to the right
	//
	// Otherwise, words may be placed adjacently, consequentially
	// adding unintended words to the puzzle
	for (i = 0; i < length; ++i) {
		// Horizontal crosswords vary on y
		// Vertical crosswords vary on x
		ch_x = dir ? x : x + i;
		ch_y = dir ? y + i : y;

		// Character falls outside WLMAX * WLMAX box -> conflict
		//
		// Note we must only check characters' attempted position
		// to be to the right of below the box, so only check for
		// x and y values greater than WLMAX - 1
		if (ch_x > WLMAX - 1 || ch_y > WLMAX - 1) return true;

		for (j = 0; j < nr; ++j) {
			if (
				// Coordinate above
				((ch_x - 1 == reserved_x[j]) && (ch_y == reserved_y[j])) ||
				// Coordinate below
				((ch_x + 1 == reserved_x[j]) && (ch_y == reserved_y[j])) ||
				// Coordinate to the left
				((ch_x == reserved_x[j]) && (ch_y - 1 == reserved_y[j])) ||
				// Coordinate to the right
				((ch_x == reserved_x[j]) && (ch_y + 1 == reserved_y[j]))
			) {
				// A special coordinate matches a reserved coordinate -> conflict
				return true;
			}
		}
	}

	// All tests passed -> no conflict
	// Awesome!
	return false;
}

// Place crossword into board
void insert_crossword(char board[WLMAX][WLMAX], Crossword *cw) {
	int i;
	int length = strlen(cw->word);

	for (i = 0; i < length; ++i) {
		if (cw->dir) {
			// Horizontal crosswords vary on y
			board[cw->x][cw->y + i] = cw->word[i];
		} else {
			// Vertical crosswords vary on x
			board[cw->x + i][cw->y] = cw->word[i];
		}
	}

	// Turn on inserted flag
	// All fields are now initialized
	cw->inserted = true;
}

// Validate that a string constitutes a word
int is_valid_word(char *string) {
	int i;
	int length = strlen(string);

	if (length < 2) {
		 // 1 -> string of length 0 or 1
		return 1;
	}

	if (length > WLMAX) {
		// 2 -> string of length greater than WLMAX
		return 2;
	}

	for (i = 0; i < length; ++i) {
		if (!isalpha(string[i])) {
			// 3 -> invalid character
			return 3;
		}
	}

	// 0 -> valid word
	return 0;
}

// Convert string to uppercase
void strupper(char *string) {
	int i;

	for (i = 0; i < strlen(string); ++i) {
		// 223 represented in binary is 11011111
		// This is the bitwise inverse of 32 (00100000)
		// In ASCII, uppercase and lowercase letters are separated by 32
		// with uppercase letters being 32 below the respective lowercase
		// letters
		// So, performing bitwise AND with 223 unto a character turns off
		// the 32 bit, forcing an uppercase letter
		string[i] &= 223;
	}
}

// Return a pointer to a randomly shuffled (anagram) version of a word
char *strana(char *string) {
	static int seed;

	int i;

	int length = strlen(string);
	char tmp;
	int ri;

	// Seed randomness with current time
	if (!seed) {
		srand(time(NULL));
		++seed;
	}

	for (i = length - 1; i > 0; --i) {
		// Get random index of rest of string
		ri = rand() % (i + 1);

		// Swap character at current index with random index
		tmp = string[i];
		string[i] = string[ri];
		string[ri] = tmp;
	}

	return string;
}

// Initialize crosswords array from words array, ordered
// by length, using an insertion sort
void init_crosswords_ordered(Crossword *cws[], char words[NWMAX][WLMAX + 1], int size) {
	int i, j;
	int length, index;

	for (i = 0; i < size; ++i) {
		length = strlen(words[i]);
		index = 0;

		// Determine proper index of element to be inserted
		for (j = 0; j < i; ++j) {
			// If the word length is less than array element
			// increment index (keep searching for spot)
			if (length < strlen(words[j])) ++index;
		}

		// Right shift existing array elements at and after index
		for (j = i; j >= index; --j) {
			cws[j] = cws[j - 1];
		}

		// Allocate memory for crossword
		cws[index] = (Crossword *)malloc(sizeof(Crossword));

		// Assign known values
		// inserted = false -> other values are uninitialized
		strcpy(cws[index]->word, words[i]);
		cws[index]->inserted = false;
	}
}

// Initialize solution board
void init_solution_board(char board[WLMAX][WLMAX]) {
	int i, j;

	for (i = 0; i < WLMAX; ++i) {
		for (j = 0; j < WLMAX; ++j) {
			board[i][j] = '.';
		}
	}
}

// Initialize puzzle board given solution board
void create_puzzle_board(char pboard[WLMAX][WLMAX], char sboard[WLMAX][WLMAX]) {
	int i, j;

	for (i = 0; i < WLMAX; ++i) {
		for (j = 0; j < WLMAX; ++j) {
			pboard[i][j] = sboard[i][j] == '.' ? '#' : ' ';
		}
	}
}

// Print board to output file
void fprint_board(FILE *outfp, char board[WLMAX][WLMAX]) {
	int i, j;

	for (i = 0; i < WLMAX + 2; ++i) {
		fprintf(outfp, "–");
	}
	fprintf(outfp, "\n");

	for (i = 0; i < WLMAX; ++i) {
		fprintf(outfp, "|");
		for (j = 0; j < WLMAX; ++j) {
			fprintf(outfp, "%c", board[i][j]);
		}
		fprintf(outfp, "|\n");
	}

	for (i = 0; i < WLMAX + 2; ++i) {
		fprintf(outfp, "–");
	}
	fprintf(outfp, "\n");
}

// Print clues to output file
void fprint_clues(FILE *outfp, Crossword *crosswords[], int size) {
	int i;

	fprintf(outfp, CLUES_HEADER);

	for (i = 0; i < size; ++i) {
		if (crosswords[i]->inserted) {
			fprintf(outfp, "%-2d, %-2d   |", crosswords[i]->x + 1, crosswords[i]->y + 1);
			fprintf(outfp, " %-6s |", crosswords[i]->dir ? "Across" : "Down");
			fprintf(outfp, " %s\n", strana(crosswords[i]->word));
		}
	}
}