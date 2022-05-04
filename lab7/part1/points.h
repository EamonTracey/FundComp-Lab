// Eamon Tracey (etracey)
// FundComp Lab 7 (1) points.h
//
// Header file for points.c
//

typedef struct Point {
	float x;
	float y;
} Point;

int pmain(char[]);
float distance(Point, Point);
float path_distance(Point[], int);
void disp_points(Point[], int);
