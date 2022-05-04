// Eamon Tracey (etracey)
// FundComp Lab 9 bounce.c
//
// Animate spinning pinwheels at each click
//

#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "gfx.h"

#define SIZE 50

const int WIDTH = 1000;
const int HEIGHT = 500;

// 2-dimensional vector structure
typedef struct {
	int x;
	int y;
} _2DVector;

int main() {
	char inp;
	int run = 1;

	// Initialize position and velocity
	int cx = WIDTH / 2;
	int cy = HEIGHT / 2;
	_2DVector vel = { 10, 10 };

	// Seed randomness
	srand(time(NULL));

	// Open window
	gfx_open(WIDTH, HEIGHT, "Bouncing Ball");

	while (run) {
		// Clear screen
		gfx_clear();

		// Draw circle
		gfx_circle(cx, cy, SIZE / 2);

		// Move circle
		cx += vel.x;
		cy += vel.y;

		// Detect collision
		if (cx <= SIZE / 2 || cx >= WIDTH - SIZE / 2) {
			// Hit left/right wall
			vel.x = -vel.x;
		}
		if (cy <= SIZE / 2 || cy >= HEIGHT - SIZE / 2) {
			// Hit left/right wall
			vel.y = -vel.y;
		}

		// Flush graphics and stagger framerate
		gfx_flush();
		usleep(10000);

		// Detect event
		if (gfx_event_waiting()) {
			inp = gfx_wait();

			switch (inp) {
				case '\x01':
					cx = gfx_xpos();
					cy = gfx_ypos();
					vel.x = rand() % 20 + 1;
					vel.y = rand() % 20 + 1;
					if (rand() & 1) vel.x = -vel.x;
					if (rand() & 1) vel.y = -vel.y;
					break;
				case '\x1B':
				case 'q':
					--run;
			}
		}
	}

	return 0;
}