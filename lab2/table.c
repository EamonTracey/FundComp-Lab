// Eamon Tracey
// Lab 2 table.c

#include <stdio.h>

int main() {
	int i, j, x, y;
	printf("X by Y Multiplication Table\n\nEnter X: ");
	scanf("%d", &x);
	printf("Enter Y: ");
	scanf("%d", &y);

	printf(" *  ");
	for (i = 1; i <= x; i++) {
		printf("%5d", i);
	}
	printf("\n   --");
	for (i = 1; i <= x; i++) {
		printf("-----");
	}
	printf("\n");

	for (i = 1; i <= y; i++) {
		printf("%2d |", i);
		for (j = 1; j <= x; j++) {
			printf("%5d", i * j);
		}
		printf("\n");
	}

	return 0;
}
