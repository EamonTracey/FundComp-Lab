#include <stdio.h>

int main() {
	printf("How many of each did the Irish score?\n\n");

	int touchdowns, extra_points, field_goals, safeties;
	printf("Touchdowns: ");	
	scanf("%d", &touchdowns);
	printf("Extra Points: ");	
	scanf("%d", &extra_points);
	printf("Field Goals: ");	
	scanf("%d", &field_goals);
	printf("Safeties: ");	
	scanf("%d", &safeties);
	
	int score = 6 * touchdowns + extra_points + 3 * field_goals + 2 * safeties;
	printf("\nIrish score: %d\n", score);

	return 0;
}
