// Eamon Tracey (etracey)
// FundComp Lab 7 (1) points.c
//
// Compute total distance of path from points input file
//
#include <math.h>
#include <stdio.h>
#include "points.h"

#define MAX_LINE_LENGTH 30
#define MAX_N_POINTS 30

// Main function that accepts points filepath as argument
// Returns exit code
int pmain(char filepath[]) {
	FILE *fp;
	char line[MAX_LINE_LENGTH];
	Point points[MAX_N_POINTS];
	int n_points = 0;

	// Verify file validity
	fp = fopen(filepath, "r");
	if (!fp) {
		printf("ERROR: The filepath %s is invalid.\n", filepath);
		return 1;
	}

	// Load points from file into array
	while (fgets(line, MAX_LINE_LENGTH, fp)) {
		sscanf(line, "%f %f", &points[n_points].x, &points[n_points].y);
		++n_points;
	}
	
	disp_points(points, n_points);
	printf("The path distance through the points is %.2f.\n", path_distance(points, n_points));

	return 0;
}

// Calculate distance between 2 points
float distance(Point p1, Point p2) {
	float xd = p1.x - p2.x, yd = p1.y - p2.y;
	return sqrt(xd * xd + yd * yd);
}

// Calculate distance of path traversed by array of points
float path_distance(Point parr[], int size) {
	float dist = 0;
	
	int i;
	for (i = 0; i < size - 1; ++i) {
		dist += distance(parr[i], parr[i + 1]);
	}

	return dist;
}

// Display array of points tabularly
void disp_points(Point parr[], int size) {
	printf("    x    |    y    \n–––––––––*––––––––––\n");
	
	int i;
	for (i = 0; i < size; ++i) {
		printf("%8.2f | %8.2f\n", parr[i].x, parr[i].y);
	}
}
