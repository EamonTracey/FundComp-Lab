// Eamon Tracey (etracey)
// FundComp Lab 4 ndfootball.c
//
// Display desired data of ND football wins/losses 1900-2021
//

#include <stdio.h>
#include "nd_data.h"

void record_for_year();
void record_for_year_range();
void winloss_for_year();
void winloss_for_year_range();
void years_with_n_wins();
void years_with_n_losses();
void years_with_least_n_wins();
void years_with_least_n_losses();
void years_with_most_n_wins();
void years_with_most_n_losses();
void years_with_winning_record();
void years_with_losing_record();

int main() {
	int choice = 0;

	printf(
		"ND Football Win/Loss Data (1900-2021)\n"
		"\n"
		"1) Record for a given year\n"
		"2) Record for a given year range\n"
		"3) Win/Loss percentage for a given year\n"
		"4) Win/loss percentage for a given year range\n"
		"5) Years with exactly n wins\n"
		"6) Years with exactly n losses\n"
		"7) Years with at least n wins\n"
		"8) Years with at least n losses\n"
		"9) Years with at most n wins\n"
		"10) Years with at most n losses\n"
		"11) Years with a winning record\n"
		"12) Years with a losing record\n"
		"13) Exit\n"
	);

	while (choice != 13) {
		printf("\nEnter choice: ");
		scanf("%d", &choice);

		switch (choice) {	
			case 1:
				record_for_year();
				break;
			case 2:
				record_for_year_range();
				break;
			case 3:
				winloss_for_year();
				break;
			case 4:
				winloss_for_year_range();
				break;
			case 5:
				years_with_n_wins();
				break;
			case 6:
				years_with_n_losses();
				break;
			case 7:
				years_with_least_n_wins();
				break;
			case 8:
				years_with_least_n_losses();
				break;
			case 9:
				years_with_most_n_wins();
				break;
			case 10:
				years_with_most_n_losses();
				break;
			case 11:
				years_with_winning_record();
				break;
			case 12:
				years_with_losing_record();
				break;
			case 13:
				break;
			default:
				printf("ERROR: Please enter a valid choice (1-13).\n");
		}
	}
	
	return 0;
}


// Display record for a given year
void record_for_year() {
	int year, n_wins, n_losses;

	printf("Enter year: ");
	scanf("%d", &year);
	if (year < 1900 || year > 2021) {
		printf("ERROR: Please enter a valid date (1900-2021)\n");
		return;
	}

	n_wins = wins[year - 1900];
	n_losses = losses[year - 1900];

	printf("Wins: %d, Losses: %d\n", n_wins, n_losses);
}

// Display record for a given year range
void record_for_year_range() {
	int year1, year2, n_wins = 0, n_losses = 0;

	printf("Enter first year: ");
	scanf("%d", &year1);
	if (year1 < 1900 || year1 > 2021) {
		printf("ERROR: Please enter a valid date (1900-2021)\n");
		return;
	}
	printf("Enter second year: ");
	scanf("%d", &year2);
	if (year2 < 1900 || year2 > 2021) {
		printf("ERROR: Please enter a valid date (1900-2021)\n");
		return;
	}

	int i;
	for (i = year1; i <= year2; ++i) {
		n_wins += wins[i - 1900];
	}
	for (i = year1; i <= year2; ++i) {
		n_losses += losses[i - 1900];
	}

	printf("Wins: %d, Losses: %d\n", n_wins, n_losses);
}

// Display number of wins and losses for a given year
void winloss_for_year() {
	int year, n_wins, n_losses;
	float total, win_rate, loss_rate;

	printf("Enter year: ");
	scanf("%d", &year);
	if (year < 1900 || year > 2021) {
		printf("ERROR: Please enter a valid date (1900-2021)\n");
		return;
	}

	n_wins = wins[year - 1900];
	n_losses = losses[year - 1900];
	total = n_wins + n_losses;
	win_rate = n_wins / total;
	loss_rate = 1 - win_rate;

	printf("Win rate: %0.2f%%, Loss rate: %0.2f%%\n", win_rate * 100, loss_rate * 100);
}

// Display number of wins and losses for a given year range
void winloss_for_year_range() {
	int year1, year2, n_wins = 0, n_losses = 0;
	float total, win_rate, loss_rate;

	printf("Enter first year: ");
	scanf("%d", &year1);
	if (year1 < 1900 || year1 > 2021) {
		printf("ERROR: Please enter a valid date (1900-2021)\n");
		return;
	}
	printf("Enter second year: ");
	scanf("%d", &year2);
	if (year2 < 1900 || year2 > 2021) {
		printf("ERROR: Please enter a valid date (1900-2021)\n");
		return;
	}

	int i;
	for (i = year1; i <= year2; ++i) {
		n_wins += wins[i - 1900];
	}
	for (i = year1; i <= year2; ++i) {
		n_losses += losses[i - 1900];
	}
	total = n_wins + n_losses;
	win_rate = n_wins / total;
	loss_rate = 1 - win_rate;

	printf("Win rate: %0.2f%%, Loss rate: %0.2f%%\n", win_rate * 100, loss_rate * 100);
}

// Display years with n wins
void years_with_n_wins() {
	int n;

	printf("Number of wins: ");
	scanf("%d", &n);
	printf("Years: ");
	
	int i;
	for (i = 0; i < sizeof(wins) / sizeof(wins[0]); ++i) {
		if (n == wins[i]) printf("%d ", i + 1900);
	}

	printf("\n");
}

// Display years with n losses
void years_with_n_losses() {
	int n;

	printf("Number of losses: ");
	scanf("%d", &n);
	printf("Years: ");
	
	int i;
	for (i = 0; i < sizeof(losses) / sizeof(losses[0]); ++i) {
		if (n == losses[i]) printf("%d ", i + 1900);
	}

	printf("\n");
}

// Display years with at least n wins
void years_with_least_n_wins() {
	int n;

	printf("Number of wins: ");
	scanf("%d", &n);
	printf("Years: ");
	
	int i;
	for (i = 0; i < sizeof(wins) / sizeof(wins[0]); ++i) {
		if (n <= wins[i]) printf("%d ", i + 1900);
	}

	printf("\n");
}

// Display years with at least n losses
void years_with_least_n_losses() {
	int n;

	printf("Number of losses: ");
	scanf("%d", &n);
	printf("Years: ");
	
	int i;
	for (i = 0; i < sizeof(losses) / sizeof(losses[0]); ++i) {
		if (n <= losses[i]) printf("%d ", i + 1900);
	}

	printf("\n");
}

// Display years with at most n wins
void years_with_most_n_wins() {
	int n;

	printf("Number of wins: ");
	scanf("%d", &n);
	printf("Years: ");
	
	int i;
	for (i = 0; i < sizeof(wins) / sizeof(wins[0]); ++i) {
		if (n >= wins[i]) printf("%d ", i + 1900);
	}

	printf("\n");
}

// Display years at most n losses
void years_with_most_n_losses() {
	int n;

	printf("Number of losses: ");
	scanf("%d", &n);
	printf("Years: ");
	
	int i;
	for (i = 0; i < sizeof(losses) / sizeof(losses[0]); ++i) {
		if (n >= losses[i]) printf("%d ", i + 1900);
	}

	printf("\n");
}

// Display years with a winning record
void years_with_winning_record() {
	printf("Years: ");
	
	int i;
	for (i = 0; i < sizeof(wins) / sizeof(wins[0]); ++i) {
		if (wins[i] >= losses[i]) printf("%d ", i + 1900);
	}

	printf("\n");
}

// Display years with a losing record
void years_with_losing_record() {
	printf("Years: ");
	
	int i;
	for (i = 0; i < sizeof(wins) / sizeof(wins[0]); ++i) {
		if (wins[i] < losses[i]) printf("%d ", i + 1900);
	}

	printf("\n");
}
