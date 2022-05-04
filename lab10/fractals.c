// Eamon Tracey (etracey)
// FundComp Lab 10 fractals.c
//
// Display 8 fractals from user input 1-8
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "fractals.h"
#include "gfx.h"

#define ANIMATE 0
#define COLOR 0

#define WIDTH 750
#define HEIGHT 750
#define MARGIN 20

const float TWOPI = 2 * M_PI;
const float TWENTYPI = 20 * M_PI;
const float TWOFIFTHSPI = 2 * M_PI / 5;
const float ONEHALFPI = M_PI / 2;
const float ONETHIRDPI = M_PI / 3;
const float ONEFIFTHPI = M_PI / 5;
const float ONESIXTHPI = M_PI / 6;
const float ONEEIGHTHPI = M_PI / 8;

int main() {
	char c;
	int run;

	if (ANIMATE) srand(time(NULL));

	gfx_open(WIDTH, HEIGHT, "Fractals");

	run = 1;
	while (run) {
		c = gfx_wait();
		gfx_clear();

		switch (c) {
			case '1':
				sierpinski_triangle(WIDTH / 2, HEIGHT - MARGIN, MARGIN, MARGIN, WIDTH - MARGIN, MARGIN);
				break;
			case '2':
				shrinking_squares(WIDTH / 2, HEIGHT / 2, (WIDTH - 2 * MARGIN) / 3);
				break;
			case '3':
				spiral_squares(WIDTH / 2, HEIGHT / 2, 0);
				break;
			case '4':
				circular_lace(WIDTH / 2, HEIGHT / 2, (WIDTH - 2 * MARGIN) / 3);
				break;
			case '5':
				snowflake(WIDTH / 2, HEIGHT / 2, (WIDTH - 2 * MARGIN) / 3);
				break;
			case '6':
				tree(WIDTH / 2, HEIGHT - MARGIN, (HEIGHT - 2 * MARGIN) / 3, ONEHALFPI);
				break;
			case '7':
				fern(WIDTH / 2, HEIGHT - MARGIN, 2 * (HEIGHT - 2 * MARGIN) / 3, ONEHALFPI);
				break;
			case '8':
				spiral_spirals(WIDTH / 2, HEIGHT / 2, 1, 0);
				break;
			case 'q':
				--run;
		}
	}

	return 0;
}

void sierpinski_triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
	// Handle base case with minimum side length 3
	if (abs(x1 - x2) <= 3) return;

	// Animate and color
	if (ANIMATE) animate();
	if (COLOR) color();

	int x12, x13, x23, y12, y13, y23;

	// Draw triangle
	triangle(x1, y1, x2, y2, x3, y3);

	x12 = (x1 + x2) / 2;
	x13 = (x1 + x3) / 2;
	x23 = (x2 + x3) / 2;
	y12 = (y1 + y2) / 2;
	y13 = (y1 + y3) / 2;
	y23 = (y2 + y3) / 2;
	
	// Recursively draw inner triangles
	sierpinski_triangle(x1, y1, x12, y12, x13, y13);
   	sierpinski_triangle(x12, y12, x2, y2, x23, y23);
   	sierpinski_triangle(x13, y13, x23, y23, x3, y3);
}

void shrinking_squares(int x, int y, int s) {
	// Handle base case with minimum side length 3
	if (s <= 3) return;

	// Animate and color
	if (ANIMATE) animate();
	if (COLOR) color();

	// Draw square
	square(x, y, s);

	s /= 2;

	// Recursively draw corner triangles
	shrinking_squares(x + s, y + s, s);
	shrinking_squares(x + s, y - s, s);
	shrinking_squares(x - s, y + s, s);
	shrinking_squares(x - s, y - s, s);
}

void spiral_squares(int x, int y, float theta) {
	// Handle base case with maximum spiral at 20PI
	if (theta > TWENTYPI) return;

	// Animate and color
	if (ANIMATE) animate();
	if (COLOR) color();

	int x1, y1;

	x1 = x + exp(0.15 * theta) * cos(theta);
	y1 = y - exp(0.15 * theta) * sin(theta);

	// Draw square
	square(x1, y1, exp(0.1 * theta));

	// Recursively draw squares
	spiral_squares(x, y, theta + ONEEIGHTHPI);
}

void circular_lace(int x, int y, int d) {
	// Handle base case with minimum diameter 1
	if (d <= 1) return;

	// Animate and color
	if (ANIMATE) animate();
	if (COLOR) color();

	// Draw circle
	gfx_circle(x, y, d);

	int i;
	float theta = ONETHIRDPI;

	// Recursively draw circles in 6-point fashion around circle
	for (i = 0; i < 6; ++i) {
		circular_lace(x + d * cos(theta), y + d * sin(theta), d / 3);
		theta += ONETHIRDPI;
	}
}

void snowflake(int x, int y, int l) {
	// Handle base case with minimum length 1
	if (l <= 1) return;

	// Animate and color
	if (ANIMATE) animate();
	if (COLOR) color();

	int i;
	float theta = TWOFIFTHSPI;

	// Recursively draw 5-pointed snowflake
	for (i = 0; i < 5; ++i) {
		gfx_line(x, y, x + l * cos(theta), y + l * sin(theta));
		snowflake(x + l * cos(theta), y + l * sin(theta), l / 3);
		theta += TWOFIFTHSPI;
	}
}

void tree(int x, int y, int l, float theta) {
	// Handle base case with minimum branch length 2
	if (l <= 2) return;

	// Animate and color
	if (ANIMATE) animate();
	if (COLOR) color();

	int x1, y1, rl;

	x1 = x + l * cos(theta);
	y1 = y - l * sin(theta);

	rl = 7 * l / 10;

	// Draw branch
	gfx_line(x, y, x1, y1);

	// Recursively draw branches, one to each side
	tree(x1, y1, rl, theta + ONESIXTHPI);
	tree(x1, y1, rl, theta - ONESIXTHPI);
}

void fern(int x, int y, int l, float theta) {
	// Handle base case with minimum branch length 2
	if (l <= 2) return;

	// Animate and color
	if (ANIMATE) animate();
	if (COLOR) color();

	int i, x1, y1, xstep, ystep, rl, xb, yb;

	x1 = x + l * cos(theta);
	y1 = y - l * sin(theta);
	
	xstep = (x1 - x) / 4;
	ystep = (y - y1) / 4;

	rl = l / 3;

	// Draw branch
	gfx_line(x, y, x1, y1);

	// Recursively draw equidistant branches, four to each side
	for (i = 1; i <= 4; ++i) {
		xb = x + i * xstep;
		yb = y - i * ystep;
		fern(xb, yb, rl, theta + ONEFIFTHPI);
		fern(xb, yb, rl, theta - ONEFIFTHPI);
	}

}

void spiral_spirals(int x, int y, int r, float theta) {
	if (r >= WIDTH / 10) return;

	// Animate and color
	if (ANIMATE) animate();
	if (COLOR) color();

	int i, xs, ys;
	float t;

	for (i = 0; i <= 2 * r; ++i) {
		t = TWOPI * i / r;
		xs = x + r * cos(2 * t) * t / TWOPI;
		ys = y - r * sin(2 * t) * t / TWOPI;

		gfx_point(xs, ys);
	}

	x = x + 3 * r * cos(theta);
	y = y - 3 * r * sin(theta);

	spiral_spirals(x, y, r + 1, theta + ONEEIGHTHPI);
}

// Draw triangle with given vertices
void triangle(int x1, int y1, int x2, int y2, int x3, int y3) {
	gfx_line(x1, y1, x2, y2);
	gfx_line(x1, y1, x3, y3);
	gfx_line(x2, y2, x3, y3);
}

// Draw square with given center and side length
void square(int x, int y, int s) {
	int x1, y1, x2, y2;
	int hs = s / 2;

	x1 = x + hs;
	y1 = y + hs;
	x2 = x - hs;
	y2 = y - hs;

	gfx_line(x1, y1, x1, y2);
	gfx_line(x1, y1, x2, y1);
	gfx_line(x1, y2, x2, y2);
	gfx_line(x2, y1, x2, y2);
}

void animate() {
	gfx_flush();
	usleep(10000);
}

void color() {
	gfx_color(rand() % 256, rand() % 256, rand() % 256);
}
