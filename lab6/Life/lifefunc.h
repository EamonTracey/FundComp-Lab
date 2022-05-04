#include <stdio.h>

extern const int SIZE;
extern const int LCHAR;

void play_interactive();
void play_batch(char[]);
void initialize_board(char[][SIZE]);
void liven_cell(char[][SIZE], int, int);
void kill_cell(char[][SIZE], int, int);
void copy_board(char[][SIZE], char[][SIZE]);
void update_display(char[][SIZE]);
void advance_game(char[][SIZE]);
int number_neighbors(char[][SIZE], int, int);
void play_forever(char[][SIZE]);
void clear();
