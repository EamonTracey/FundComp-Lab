// Eamon Tracey
// Lab 3 menucalc.c

#include <stdio.h>

#define PROMPT "\nWhat would you like to do?\n1 for addition\n2 for subtraction\n3 for multiplication\n4 for division\n5 to exit\nEnter your choice: "

void add(double, double);
void subtract(double, double);
void multiply(double, double);
void divide(double, double);

int main() {
	int choice = 0;
	double a, b;

	printf(PROMPT);
	scanf("%d", &choice);
	
	while (choice != 5) {
		if (!(choice > 0 && choice < 6)) {
			printf("ERROR: Please choose an option 1-5.\n");
			continue;
		}
		printf("Enter two numbers: ");
		scanf("%lf%lf", &a, &b);
		if (choice == 1) {
			add(a, b);
		} else if (choice == 2) {
			subtract(a, b);
		} else if (choice == 3) {
			multiply(a, b);
		} else {
			if (b == 0) {
				printf("ERROR: Cannot divide by zero.\n");
				continue;
			}
			divide(a, b);
		}

		printf(PROMPT);
		scanf("%d", &choice);
	}

	printf("Goodbye!\n");

	return 0;
}

// Add 2 numbers, print output
void add(double a, double b) {
	printf("(%lf) + (%lf) = %lf\n", a, b, a + b);
}

// Subtract 2 numbers, print output
void subtract(double a, double b) {
	printf("(%lf) - (%lf) = %lf\n", a, b, a - b);
}

// Multiply 2 numbers, print output
void multiply(double a, double b) {
	printf("(%lf) * (%lf) = %lf\n", a, b, a * b);
}

// Divide 2 numbers, print output
void divide(double a, double b) {
	printf("(%lf) / (%lf) = %lf\n", a, b, a / b);
}
