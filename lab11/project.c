// Eamon Tracey (etracey)
// FundComp Lab 11 Final project.c
//
// Play tic tac toe and pong
//

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "gfx2.h"
#include "project.h"

#define SIZE 700

const int SIZED2 = SIZE / 2;
const int SIZED4 = SIZE / 4;
const int SIZED5 = SIZE / 5;
const int SIZED8 = SIZE / 8;
const int SIZED20 = SIZE / 20;

int main() {
	// Seed randomness
	srand(time(NULL));

	Player p1;
	Player p2;

	// Open graphics window
	gfx_open(SIZE, SIZE, "Lab 11 Final Project");

	// Set font
	gfx_changefont("12x24");

	// Initialize players
	init_player(&p1);
	init_player(&p2);

	// Run until quit from menu
	while (menu(&p1, &p2)) {}

	return 0;
}

// Display text centered at x, y (assuming 12 * 24)
void textc(int x, int y, const char *text) {
	gfx_text(x - 6 * strlen(text), y + 12, text);
}

// Initialize player with name and 0 wins
void init_player(Player *p) {
	char prompt[50];

	char inp;
	char name[16];
	int l = 0;

	gfx_text(SIZED4, SIZED2, "Enter name:");

	do {
		inp = gfx_wait();

		if (!isalpha(inp)) {
			// Delete character upon backspace
			if (inp == 8 && l > 0) {
				name[--l] = 0;

				gfx_clear();
				sprintf(prompt, "Enter name: %s", name);
				gfx_text(SIZED4, SIZED2, prompt);
			}
			// Skip non-alpha characters
			continue;
		}

		// Prevent overflow
		if (l == 15) {
			continue;
		}

		name[l++] = inp;
		name[l] = 0;

		sprintf(prompt, "Enter name: %s", name);
		gfx_text(SIZED4, SIZED2, prompt);
	} while (inp != 13 || l == 0);

	strcpy(p->name, name);
	p->wins = 0;

	gfx_clear();
	gfx_flush();
}

// Display start-up menu
int menu(Player *p1, Player *p2) {
	char p1msg[50];
	char p2msg[50];

	sprintf(p1msg, "%s wins: %d", p1->name, p1->wins);
	sprintf(p2msg, "%s wins: %d", p2->name, p2->wins);

	gfx_clear();

	gfx_color(255, 255, 255);
	textc(SIZED2, SIZED20, "Welcome!");
	textc(SIZED2, SIZED4, "Press 1 for Tic Tac Toe");
	textc(SIZED2, SIZED4 + 48, "Press 2 for Pong");
	textc(SIZED2, SIZED4 + 96, "Press 3 for Help");
	textc(SIZED4, SIZE - SIZED4, p1msg);
	textc(SIZE - SIZED4, SIZE - SIZED4, p2msg);

	switch (gfx_wait()) {
		case '1':
			tic_tac_toe(p1, p2);
			break;
		case '2':
			pong(p1, p2);
			break;
		case '3':
			help();
			break;
		case 'q':
			return 0;
	}

	return 1;
}

// Play tic tac toe game
void tic_tac_toe(Player *p1, Player *p2) {
	// 2D array represents game
	// 0 -> Spot not filled
	// 1 -> Player 1 X
	// 2 -> Player 2 O
	int board[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };

	int row, col;
	int winner = 0;
	int turn = 1;

	char go1[50], go2[50];
	sprintf(go1, "%s's turn", p1->name);
	sprintf(go2, "%s's turn", p2->name);

	char winmsg[40];

	// Clear window from previous
	gfx_clear();
	gfx_flush();

	while (1) {
		// Draw title
		gfx_color(255, 255, 255);
		textc(SIZED2, SIZED20, "Tic Tac Toe");
		if (turn % 2) {
			textc(SIZED2, SIZED8, go1);
		} else {
			textc(SIZED2, SIZED8, go2);
		}

		draw_board(board);

		if (gfx_wait() == (char)1) {
			row = gfx_ypos() / SIZED5;
			col = gfx_xpos() / SIZED5;

			// Hitbox within bounds of tic tac toe board
			if (row >= 1 && row <= 3 && col >= 1 && col <= 3 && !board[row - 1][col - 1]) {
				board[row - 1][col - 1] = turn % 2 ? 1 : 2;
			} else {
				continue;
			}
		}

		// Check win
		winner = check_board_win(board);
		if (winner) {
			draw_board(board);

			sprintf(winmsg, "%s wins!", winner == 1 ? p1->name : p2->name);

			gfx_color(255, 192, 203);
			textc(SIZED2, SIZE - SIZED8, winmsg);
			gfx_color(0, 255, 0);
			textc(SIZED2, SIZE - SIZED20, "Press ENTER to continue");
			gfx_flush();

			while (gfx_wait() != 13) {}
			break;
		}

		// Check full board
		if (turn == 9) {
			draw_board(board);

			gfx_color(255, 192, 203);
			textc(SIZED2, SIZE - SIZED8, "Neither player wins!");
			gfx_color(0, 255, 0);
			textc(SIZED2, SIZE - SIZED20, "Press ENTER to continue");
			gfx_flush();

			while (gfx_wait() != 13) {}
			break;
		}

		// Change player turn
		++turn;

		gfx_clear();
		gfx_flush();
	}

	switch (winner) {
		case 0:
			return;
		case 1:
			++p1->wins;
			break;
		case 2:
			++p2->wins;
			break;
	}
}

// Draw tic tac toe board
void draw_board(int board[3][3]) {
	int i, j;

	// Draw frame
	gfx_color(255, 255, 255);
	gfx_fill_rectangle(2 * SIZED5 - 5, SIZED5, 10, 3 * SIZED5);
	gfx_fill_rectangle(3 * SIZED5 - 5, SIZED5, 10, 3 * SIZED5);
	gfx_fill_rectangle(SIZED5, 2 * SIZED5 - 5, 3 * SIZED5, 10);
	gfx_fill_rectangle(SIZED5, 3 * SIZED5 - 5, 3 * SIZED5, 10);

	for (i = 0; i < 3; ++i) {
		for (j = 0; j < 3; ++j) {
			switch(board[i][j]) {
				// Player 1 -> draw X
				case 1:
					gfx_color(255, 0, 0);
					gfx_line((j + 1) * SIZED5 + 10, (i + 1) * SIZED5 + 10, (j + 2) * SIZED5 - 10, (i + 2) * SIZED5 - 10);
					gfx_line((j + 2) * SIZED5 - 10, (i + 1) * SIZED5 + 10, (j + 1) * SIZED5 + 10, (i + 2) * SIZED5 - 10);
					break;
				// Player 2 -> draw O
				case 2:
					gfx_color(0, 0, 255);
					gfx_circle((j + 1.5) * SIZED5, (i + 1.5) * SIZED5, SIZED5 / 2 - 10);
					break;
			}
		}
	}

	gfx_flush();
}

// Determine who wins (if anyone) a given board
int check_board_win(int board[3][3]) {
	int i;

	// Check horizontal
	for (i = 0; i < 3; ++i) {
		if (board[i][0] && board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
			return board[i][0];
		}
	}

	// Check vertical
	for (i = 0; i < 3; ++i) {
		if (board[0][i] && board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
			return board[0][i];
		}
	}

	// Check diagonal
	if (
		(board[0][0] && board[0][0] == board[1][1] && board[0][0] == board[2][2]) ||
		(board[0][2] && board[0][2] == board[1][1] && board[0][2] == board[2][0])
	) {
		return board[1][1];
	}

	return 0;
	
}

// Play pong
void pong(Player *p1, Player *p2) {
	Paddle paddle1 = (Paddle){ SIZED2, SIZE - SIZED8, 200};
	Paddle paddle2 = (Paddle){ SIZED2, SIZED8, 200};
	Ball ball = (Ball){ randint(0, SIZE), SIZE - SIZED5, randint(12, 20), randint(-12, -10) };

	int frames = 0;
	char lengthmsg[20];
	int winner;

	char winmsg[40];

	while (1) {
		// Draw title
		gfx_color(255, 255, 255);
		textc(SIZED2, SIZED20, "Pong");
		sprintf(lengthmsg, "paddle length: %d", paddle1.length);
		textc(SIZED2, SIZE - SIZED20, lengthmsg);

		// Bounce ball off walls
		if (ball.x < 0 || ball.x > SIZE) {
			ball.vx = -ball.vx;
		}

		// Bounce ball off bottom paddle
		if (abs(ball.y - paddle1.y) <= 15 && ball.x >= paddle1.x - paddle1.length && ball.x <= paddle1.x + paddle1.length) {
			ball.vy = -ball.vy;
			ball.y -= 30;
		}

		// Bounce ball off top paddle
		if (abs(ball.y - paddle2.y) <= 15 && ball.x >= paddle2.x - paddle2.length && ball.x <= paddle2.x + paddle2.length) {
			ball.vy = -ball.vy;
			ball.y += 30;
		}

		// Move ball
		ball.x += ball.vx;
		ball.y += ball.vy;

		// Detect paddle movement
		if (gfx_event_waiting()) {
			switch (gfx_wait()) {
				case 'a':
					paddle1.x -= 20;
					break;
				case 's':
					paddle1.x += 20;
					break;
				case 'k':
					paddle2.x -= 20;
					break;
				case 'l':
					paddle2.x += 20;
					break;
			}
		}

		// Draw ball
		gfx_fill_circle(ball.x, ball.y, 10);

		// Draw paddles
		gfx_color(255, 0, 0);
		draw_paddle(paddle1);
		gfx_color(0, 0, 255);
		draw_paddle(paddle2);

		// Check win
		if (ball.y < 0) {
			winner = 1;
			break;
		} else if (ball.y > SIZE) {
			winner = 2;
			break;
		}

		usleep(20000);

		++frames;
		if (frames % 25 == 0 && paddle1.length > 10) {
			paddle1.length -= 5;
			paddle2.length -= 5;
		}

		gfx_clear();
		gfx_flush();
	}

	sprintf(winmsg, "%s wins!", winner == 1? p1->name : p2->name);
	gfx_color(255, 192, 203);
	textc(SIZED2, SIZED2, winmsg);
	gfx_color(0, 255, 0);
	textc(SIZED2, SIZE - SIZED4, "Press ENTER to continue");

	while (gfx_wait() != 13) {}

	if (winner == 1) {
		++p1->wins;
	} else {
		++p2->wins;
	}
}

// Draw pong paddle
void draw_paddle(Paddle paddle) {
	gfx_fill_rectangle(paddle.x - paddle.length / 2, paddle.y - 2, paddle.length, 4);
	gfx_flush();
}

// Generate random integer in [min, max]
int randint(int min, int max) {
	return (rand() % (max - min + 1)) + min;
}

// Display help menu
void help() {
	gfx_clear();

	textc(SIZED2, SIZED20, "Help");

	textc(SIZED2, SIZED4, "Tic Tac Toe:");
	textc(SIZED2, SIZED4 + 24, "Use the mouse clicker to place X's and O's");
	textc(SIZED2, SIZED4 + 48, "Players alternate turns");
	textc(SIZED2, SIZED2, "Pong:");
	textc(SIZED2, SIZED2 + 24, "Player 1 use 'a' and 's' to move left and right");
	textc(SIZED2, SIZED2 + 48, "Player 2 use 'k' and 'l' to move left and right");
	textc(SIZED2, SIZED2 + 72, "Don't let the ball pass your paddle");

	gfx_color(0, 255, 0);
	textc(SIZED2, SIZE - SIZED20, "Press ENTER to continue");

	while (gfx_wait() != 13) {}
}
