// Eamon Tracey (etracey)
// FundComp Lab 4 grades.c
//
// Write functions to compute the average and standard deviation of an integer array of grades
//

#include <math.h>
#include <stdio.h>

float average(int[], int);
float standard_deviation(int[], int);

int main() {
	int grades[] = {
		96, 73, 62, 87, 80, 63, 93, 79, 71, 99,
		82, 83, 80, 97, 89, 82, 93, 92, 95, 89,
		71, 97, 91, 95, 63, 81, 76, 98, 64, 86,
		74, 79, 98, 82, 77, 68, 87, 70, 75, 97,
		71, 94, 68, 87, 79
	};
	int length = sizeof(grades) / 4;

	printf("There are %d grades.\n", length);

	printf("Average: %f\n", average(grades, length));
	printf("Standard Deviation: %f\n", standard_deviation(grades, length));
	
	return 0;
}

// Computes the average of an integer array
float average(int numbers[], int length) {
	float sum;

	int i;
	for (i = 0; i < length; ++i) {
		sum += numbers[i];
	}

	return sum / length;
}

// Computes the standard deviation of an integer array
// sd = sqrt(sum((element - mean)^2) / number_of_elements)
float standard_deviation(int numbers[], int length) {
	float mean = average(numbers, length);
	float deviations_squared;
	
	int i;
	for (i = 0; i < length; ++i) {
		deviations_squared += pow(numbers[i] - mean, 2);
	}

	return sqrt(deviations_squared / length);
}
