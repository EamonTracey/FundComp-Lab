// Eamon Tracey (etracey)
// FundComp Lab 9 funanim.c
//
// Animate bouncing ball
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "gfx.h"

#define SIZE 50

const int WIDTH = 500;
const int HEIGHT = 500;
const float rot = M_PI / 8;

typedef struct {
	int x;
	int y;
	float rad;
	int r;
	int g;
	int b;
} Pinwheel;

void draw_pinwheel(Pinwheel);

int main() {
	printf("Click anywhere in the window to deploy a pinwheel\n");
	fflush(stdout);

	int i;
	char inp;
	int run = 1;

	// Seed randomness
	srand(time(NULL));

	// Initialize Pinwheels array
	int npws = 0;
	Pinwheel pws[256];

	// Open window
	gfx_open(WIDTH, HEIGHT, "Rotating Animation");

	while (run) {
		// Clear screen
		gfx_clear();

		// Draw pinwheels
		for (i = 0; i < npws; ++i) {
			gfx_color(pws[i].r, pws[i].g, pws[i].b);
			draw_pinwheel(pws[i]);

			// Advance rotation
			pws[i].rad += rot;
		}

		// Flush window and stagger framerate
		gfx_flush();
		usleep(100000);

		// Detect input
		if (gfx_event_waiting()) {
			inp = gfx_wait();

			switch (inp) {
				case '\x01':
					pws[npws++] = (Pinwheel){
						gfx_xpos(),
						gfx_ypos(),
						0,
						rand() % 255,
						rand() % 255,
						rand() % 255
					};
					break;
				case '\x1B':
					npws = 0;
					break;
				case 'q':
					--run;
			}
		}
	}

	return 0;
}

// Draw four-pointed pinwheel
void draw_pinwheel(Pinwheel pw) {
	float c = cos(pw.rad);
	float s = sin(pw.rad);

	float x1 = -SIZE * s;
	float y1 = SIZE * c;
	float x2 = SIZE * c;
	float y2 = SIZE * s;

	gfx_line(pw.x, pw.y, pw.x + x1, pw.y + y1);
	gfx_line(pw.x, pw.y, pw.x + x2, pw.y + y2);
	gfx_line(pw.x, pw.y, pw.x - x1, pw.y - y1);
	gfx_line(pw.x, pw.y, pw.x - x2, pw.y - y2);
}
