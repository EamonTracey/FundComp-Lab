#include <math.h>
#include <stdio.h>

int main() {
	printf("Calculate the magnitude of a 3-dimensional vector.\n\n");
	
	double x_comp, y_comp, z_comp;
	printf("x-component: ");
	scanf("%lf", &x_comp);
	printf("y-component: ");
	scanf("%lf", &y_comp);
	printf("z-component: ");
	scanf("%lf", &z_comp);

	double magnitude = sqrt(x_comp * x_comp + y_comp * y_comp + z_comp * z_comp);

	printf("\nMagnitude: %f\n", magnitude);

	return 0;
}
