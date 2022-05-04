// Eamon Tracey (etracey)
// FundComp Lab 7 (2) states.c
//
// Explore USA states information from CSV 
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "states.h"

#define MAX_LINE_LENGTH 100
#define MAX_ABBR_LENGTH 3
#define MAX_NAME_LENGTH 20
#define N_STATES 50

#define MENU "\n1) All states\n2) All states (by founding year)\n3) State from abbreviation\n4) State's capital\n5) State's founding year\n6) States founded in year\n7) States founded in year range\n8) Quit\nEnter option: "

// Main function that accepts states CSV filepath as argument
//
// Returns exit code
int smain(char filepath[]) {
	FILE *fp;	
	State states[N_STATES];

	// Verify file validity
	fp = fopen(filepath, "r");
	if (!fp) {
		printf("ERROR: The filepath %s is invalid.\n", filepath);
		return 1;
	}

	// Load states from CSV
	fload_states(states, fp);

	int c = 0;
	printf("USA States Explorer\n");
	while (c != 8) {
		printf(MENU);
		scanf("%d", &c);
		switch (c) {
			case 1:
				disp_states(states, N_STATES);
				break;
			case 2:
				disp_ostates(states, N_STATES);
				break;
			case 3:
				state_from_abbr(states, N_STATES);
				break;
			case 4:
				state_capital(states, N_STATES);
				break;
			case 5:
				state_year(states, N_STATES);
				break;
			case 6:
				states_in_year(states, N_STATES);
				break;
			case 7:
				states_in_year_range(states, N_STATES);
				break;
			case 8:
				// Exit loop
				break;
			default:
				printf("Invalid option. Choose in range [1-?].\n");
		}
	}


	return 0;
}

// Load states into array from CSV file pointer
void fload_states(State states[], FILE *file) {
	char line[MAX_LINE_LENGTH];

	int i = 0;
	while (fgets(line, MAX_LINE_LENGTH, file)) {
		strcpy(states[i].abbr, strtok(line, ","));
		strcpy(states[i].name, strtok(NULL, ","));
		strcpy(states[i].capital, strtok(NULL, ","));
		states[i++].year = atoi(strtok(NULL, ","));
	}
}

// Display array of states tabularly
void disp_states(State states[], int size) {
	printf("\nABBR   | State                | Capital City         | Year\n–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––\n");

	int i;
	for (i = 0; i < size; ++i) {
		printf(" %-5s | %-20s | %-20s | %-5d\n", states[i].abbr, states[i].name, states[i].capital, states[i].year);
	}
}

// Display states ordered by year
//
// The function uses a bubble sort to order the states by founding year.
//
// Bubble sort works by checking each consecutive pair of states in an array
// and swapping the pair elements if necessary.
//
// The sort repeats this process until it does not swap any pairs, indicating
// a sorted array.
void disp_ostates(State states[], int size) {
	// Copy array
	State ostates[size];
	memcpy(ostates, states, size * sizeof(State));

	// Bubble sort implementation
	int i, j, swapped;
	for (i = 0; i < size - 1; ++i) {
		swapped = 0;
		//  Check consecutive states, swap 2 states if unordered by year
		for (j = 0; j < size - i - 1; ++j) {
			if (ostates[j].year > ostates[j + 1].year) {
				swap_states(&ostates[j], &ostates[j + 1]);
				++swapped; // Indicate swap
			}
		}
		// Passthrough without swap means array is sorted
		if (!swapped) break;
	}

	// Display ordered array
	disp_states(ostates, size);
}

// Swap 2 State variables
void swap_states(State *s1, State *s2) {
	State tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

// Display state given abbreviation
void state_from_abbr(State states[], int size) {
	char abbr[MAX_NAME_LENGTH];

	printf("\nEnter abbreviation: ");
	scanf("%s", abbr);

	int i;
	for (i = 0; i < size; ++i) {
		if (!strcasecmp(states[i].abbr, abbr)) {
			disp_states(&states[i], 1);
			return;
		}
	}

	printf("ERROR: No state with abbreviation %s.\n", abbr);
}

// Display state capital given name or abbreviation
void state_capital(State states[], int size) {
	char input[MAX_NAME_LENGTH];

	printf("\nEnter state name or abbreviation: ");
	getchar(); // Eat newline left by scanf
	fgets(input, MAX_NAME_LENGTH, stdin);
	input[strlen(input) - 1] = '\0'; // Replace newline from fgets with null char

	int i;
	for (i = 0; i < size; ++i) {
		if (!strcasecmp(states[i].abbr, input)) {
			printf("%s's capital city is %s.\n", states[i].name, states[i].capital);
			return;
		}
		if (!strcasecmp(states[i].name, input)) {
			printf("%s's capital city is %s.\n", states[i].name, states[i].capital);
			return;
		}
	}

	printf("ERROR: No state with name/abbreviation %s.\n", input);
}

// Display state founding year given name or abbreviation
void state_year(State states[], int size) {
	char input[MAX_NAME_LENGTH];

	printf("\nEnter state name or abbreviation: ");
	getchar(); // Eat newline left by scanf
	fgets(input, MAX_NAME_LENGTH, stdin);
	input[strlen(input) - 1] = '\0'; // Replace newline from fgets with null char

	int i;
	for (i = 0; i < size; ++i) {
		if (!strcasecmp(states[i].abbr, input)) {
			printf("%s was founded in %d.\n", states[i].name, states[i].year);
			return;
		}
		if (!strcasecmp(states[i].name, input)) {
			printf("%s was founded in %d.\n", states[i].name, states[i].year);
			return;
		}
	}

	printf("ERROR: No state with name/abbreviation %s.\n", input);
}

// Display states founded in given year
void states_in_year(State states[], int size) {
	int year, c = 0;
	State valid_states[size];

	printf("\nEnter year: ");
	scanf("%d", &year);

	int i;
	for (i = 0; i < size; ++i) {
		if (states[i].year == year) {
			valid_states[c++] = states[i];
		}
	}

	if (c) {
		disp_states(valid_states, c);
	} else {
		printf("No states founded in year %d.\n", year);
	}
}

// Display states founded in given year range (inclusive)
void states_in_year_range(State states[], int size) {
	int year1, year2, c = 0;
	State valid_states[size];

	printf("\nEnter start year: ");
	scanf("%d", &year1);
	printf("Enter end year: ");
	scanf("%d", &year2);

	if (year1 > year2) {
		printf("ERROR: Start year must be earlier than or same as end year.\n");
		return;
	}

	int i;
	for (i = 0; i < size; ++i) {
		if (states[i].year >= year1 && states[i].year <= year2) {
			valid_states[c++] = states[i];
		}
	}

	if (c) {
		disp_states(valid_states, c);
	} else {
		printf("No states founded in range %d-%d.\n", year1, year2);
	}
}
