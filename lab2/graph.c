// Eamon Tracey
// Lab 2 graph.c

#include <math.h>
#include <stdio.h>

int main() {
	float i, j, output, min_x, max_x, min_y, max_y;
	min_x = max_x = 0;
	min_y = max_y = 10 * (exp(sin(0)) * cos(0) + 1.5);

	printf("Plot for y = 10 * (e^(sin(x)) * cos(x) + 1.5) for x from 0 to 19.8\n\n");
	printf("   X      Y\n");

	for (i = 0; i <= 20; i += 0.2) {
		output = 10 * (exp(sin(i)) * cos(i) + 1.5);
		if (output < min_y) {
			min_y = output;
			min_x = i;
		} else if (output > max_y) {
			max_y = output;
			max_x = i;
		}
		printf("%5.2f   %5.2f   ", i, output);
		for (j = 0; j < output; j++) {
			printf("*");
		}
		printf("\n");
	}
	
	printf("The maximum of %.2f was at %.2f\n", max_y, max_x);
	printf("The minimum of %.2f was at %.2f\n", min_y, min_x);

	return 0;
}
