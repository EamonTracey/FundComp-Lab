// Eamon Tracey
// Lab 3 quadratics.c

#include <math.h>
#include <stdio.h>

double discriminant(double, double, double);

int main() {
	double a, b, c, disc;
	double x1, x2;

	printf("Enter the coefficients (a,b,c) of a quadratic equation (a=0 to exit): ");
	scanf("%lf%lf%lf", &a, &b, &c);

	while (a != 0) {
		disc = discriminant(a, b, c);
		if (disc < 0) {
			printf("No real solutions exist.\n");
		} else if (disc == 0) {
			x1 = -b / (2 * a);
			printf("There exists one solution:\nx1: %lf\n", x1);
		} else {
			x1 = (-b - sqrt(disc)) / (2 * a);
			x2 = (-b + sqrt(disc)) / (2 * a);
			printf("There exist two solutions:\nx1: %lf\nx2: %lf\n", x1, x2);
		}
		printf("Enter the coefficients (a,b,c) of a quadratic equation: ");
		scanf("%lf%lf%lf", &a, &b, &c);
	}

	return 0;
}

// Compute discriminant of quadratic equation
double discriminant(double a, double b, double c) {
	return pow(b, 2) - 4 * a * c;
}
