// Eamon Tracey (etracey)
// FundComp Lab 9 symbol.c
//
// Draw colored symbols on X11 window given input
//

#include <math.h>
#include "gfx.h"

#define SIZE 50

const int WIDTH = 500;
const int HEIGHT = 500;

void square(int, int);
void circle(int, int);
void triangle(int, int);
void ngon(int, int, int);

int main () {
	char inp;
	int run = 1;

	// Open window
	gfx_open(WIDTH, HEIGHT, "Symbolic Typewriter");

	// Enter window loop
	while (run) {
		// Wait for user input
		inp = gfx_wait();

		switch (inp) {
			case '\x01':
				gfx_color(0, 0, 255);
				square(gfx_xpos(), gfx_ypos());
				break;
			case 'c':
				gfx_color(255, 255, 255);
				circle(gfx_xpos(), gfx_ypos());
				break;
			case 't':
				gfx_color(0, 255, 0);
				triangle(gfx_xpos(), gfx_ypos());
				break;
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				gfx_color(255, 0, 255);
				ngon((int)(inp - 48), gfx_xpos(), gfx_ypos());
				break;
			case '\x1B':
				gfx_clear();
				break;
			case 'q':
				--run;
				break;
			default:
				// No default implementation
				break;
		}
		
		// Flush graphics to window
		gfx_flush();
	}

	return 0;
}

// Draw a square with side length SIZE at center (x, y)
void square(int x, int y) {
	int nx, px, ny, py;

	// Calculate x and y coordinates of square vertices
	nx = x - SIZE / 2;
	px = x + SIZE / 2;
	ny = y - SIZE / 2;
	py = y + SIZE / 2;

	// Draw lines
	gfx_line(nx, ny, nx, py);
	gfx_line(nx, ny, px, ny);
	gfx_line(px, py, px, ny);
	gfx_line(px, py, nx, py);
}

// Draw a circle with diameter SIZE at center (x, y)
void circle(int x, int y) {
	gfx_circle(x, y, SIZE / 2);
}

// Draw an isosceles triangle with width and height SIZE at center (x, y)
void triangle(int x, int y) {
	int nx, cx, px, ny, py;

	// Calculate x and y coordinates of triangle vertices
	nx = x - SIZE / 2;
	cx = x;
	px = x + SIZE / 2;
	ny = y - SIZE / 2;
	py = y + SIZE / 2;

	// Draw lines
	gfx_line(nx, py, px, py);
	gfx_line(nx, py, cx, ny);
	gfx_line(px, py, cx, ny);
}

// Draw an ngon to fit in a circle of diameter SIZE at center (x, y)
void ngon(int n, int x, int y) {
	int i;
	int lx, ly, fx, fy;

	// Compute angle, sin, and cos
	float ang = 2 * M_PI / n;
	float s = sin(ang);
	float c = cos(ang);

	// Define first point
	lx = x;
	ly = y - SIZE / 2;

	for (i = 0; i < n; ++i) {
		// Rotate point
		fx = (lx - x) * c - (ly - y) * s + x;
		fy = (ly - y) * c + (lx - x) * s + y;

		// Draw line
		gfx_line(lx, ly, fx, fy);

		// Update last point
		lx = fx;
		ly = fy;
	}
}
