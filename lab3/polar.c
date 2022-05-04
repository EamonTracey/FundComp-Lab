// Eamon Tracey
// Lab 3 polar.c

#include <math.h>
#include <stdio.h>

int get_quadrant(double, double);
double get_radius(double, double);
double get_angle(double, double);
void show_info(int, double, double);

int main() {
	double x, y;
	int quadrant;
	double radius, angle;
	
	printf("Enter coordinates (x,y) of cartesian point: ");
	scanf("%lf%lf", &x, &y);

	quadrant = get_quadrant(x, y);
	radius = get_radius(x, y);
	angle = get_angle(x, y);

	show_info(quadrant, radius, angle);
}

// Get quadrant given cartesian coordinates
int get_quadrant(double x, double y) {
	return x > 0 ? (y > 0 ? 1 : 4) : (y > 0 ? 2 : 3);
}

// Get radius given cartesian coordinates
double get_radius(double x, double y) {
	return sqrt(pow(x, 2) + pow(y, 2));
}

// Get angle given cartesian coordinates
double get_angle(double x, double y) {
	return atan2(y, x);
}

// Print quadrant, radius, and angle
void show_info(int quadrant, double radius, double angle) {
	printf("The point exists in Quadrant %d\n", quadrant);
	printf("A corresponding polar coordinate (in degrees) is (%lf, %lf)\n", radius, angle * 180 / M_PI);
}
