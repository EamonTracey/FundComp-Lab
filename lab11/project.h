// Eamon Tracey (etracey)
// FundComp Lab 11 Final project.h
//
// Declare prototypes for project.c
//

// General
typedef struct {
	char name[32];
	int wins;
} Player;

void text_better(int, int, const char *);
void init_player(Player *);

// Menu
int menu(Player *, Player *);

// Help
void help();

// Tic tac toe
void tic_tac_toe(Player *, Player *);
void draw_board(int[3][3]);
int check_board_win(int board[3][3]);

// Pong
typedef struct {
	int x;
	int y;
	int length;
} Paddle;

typedef struct {
	int x;
	int y;
	int vx;
	int vy;
} Ball;

void pong(Player *, Player *);
void draw_paddle(Paddle);
int randint(int, int);