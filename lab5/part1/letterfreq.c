// Eamon Tracey (etracey)
// FundComp Lab 5 letterfreq.c
//
// Justify Scrabble letter values
//

#include <ctype.h>
#include <stdio.h>

// Generalize alphabet
#define ALPHABET_LENGTH 26
#define ALPHABET_START 97 

void display_data(char[ALPHABET_LENGTH], int[ALPHABET_LENGTH], int);
int sum(int[], int);

int main() {
	// Read filepath from user
	char filepath[30];
	printf("Filepath: ");
	scanf("%s", filepath);

	// Verify filepath exists
	FILE *fp = fopen(filepath, "r");
	if (!fp) {
		printf("ERROR: File %s does not exist.\n", filepath);
		return 1;
	}

	// Initialize array of zeroes and other_count to zero
	int letter_counts[ALPHABET_LENGTH], other_count, i;
	for (i = 0; i < ALPHABET_LENGTH; ++i) {
		letter_counts[i] = 0;
	}
	other_count = 0;

	// Scan file
	char current_char;
	while (1) {
		fscanf(fp, "%c", &current_char);
		if (feof(fp)) break; // Exit when file ends
		if (isalpha(current_char)) {
			current_char = tolower(current_char); // Case-insensitivity
			++letter_counts[current_char - ALPHABET_START]; // Increment corresponding array element
		} else {
			++other_count; // Count non-alphabet characters
		}
	}
	fclose(fp);
	
	// Display data
	printf("\n");
	display_data(filepath, letter_counts, other_count);

	return 0;
}

// Return sum of integer array
int sum(int nums[], int size) {
	int sum_ = 0, i;
	for (i = 0; i < size; ++i) {
		sum_ += nums[i];
	}
	return sum_;
}

// Beautifully display file letter frequency data given filepath, letter counts, other character count
void display_data(char filepath[ALPHABET_LENGTH], int letter_counts[ALPHABET_LENGTH], int other_count) {
	int n_letters, n_chars;
	float letter_percentages[ALPHABET_LENGTH];
	
	// Count total letters and characters
	n_letters = sum(letter_counts, ALPHABET_LENGTH);
	n_chars = n_letters + other_count;
	
	// Calculate letter percentages
	int i;
	for (i = 0; i < ALPHABET_LENGTH; ++i) {
		letter_percentages[i] = letter_counts[i] / (float)n_letters * 100;
	}	

	// Display general information
	printf("Summary for %s:\n\n", filepath);
	printf("Number of characters: %d\n", n_chars);
	printf("Number of letters: %d\n\n", n_letters);

	// Format and display letter counts
	printf("Letter counts:\n");
	for (i = 0; i < ALPHABET_LENGTH; ++i) {
		printf("%c:%8d  ", ALPHABET_START + i, letter_counts[i]);
		if ((i + 1) % 6 == 0) printf("\n");
	}
	if ((i + 1) % 6 != 0) printf("\n");
	printf("\n");

	// Format and display letter percentages
	printf("Letter percentages:\n");
	for (i = 0; i < ALPHABET_LENGTH; ++i) {
		printf("%c:%7.2f%%  ", ALPHABET_START + i, letter_percentages[i]);
		if ((i + 1) % 6 == 0) printf("\n");
	}
	if ((i + 1) % 6 != 0) printf("\n");
}
