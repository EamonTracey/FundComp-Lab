// Eamon Tracey (etracey)
// FundComp Lab 5 mysayings.c
//
// Sayings database manager
//

#include <stdio.h>
#include <string.h>

#define MAX_SAYING_LENGTH 256
#define MAX_FILEPATH 30
#define MAX_SAYINGS 50
#define MENU "\n1) Display all database sayings\n2) Display database size\n3) Display sayings containing substring\n4) Enter new saying into database\n5) Swap two sayings\n6) Save database to file\n7) Exit\n\nEnter option: "

void display_all(char[][MAX_SAYING_LENGTH], int);
void display_sayings_with_word(char[][MAX_SAYING_LENGTH], int);
void enter_new_saying(char[][MAX_SAYING_LENGTH], int *);
void swap_two_sayings(char[][MAX_SAYING_LENGTH], int);
void save_database_to_file(char[][MAX_SAYING_LENGTH], int);

int main() {
	FILE *fp;
	char filepath[MAX_FILEPATH], database[MAX_SAYINGS][MAX_SAYING_LENGTH];
	int option, size = 0;

	// Get filepath, validate existence
	printf("Load database from file: ");
	scanf("%s", filepath);
	fp = fopen(filepath, "r");
	if (!fp) {
		printf("ERROR: File %s does not exist\n", filepath);
		return 1;
	}

	// Load database from file
	while (fgets(database[size], MAX_SAYING_LENGTH, fp)) {
		database[size][strlen(database[size]) - 1] = '\0'; // Replace newline with null char
		++size;
	}
	fclose(fp);

	// Continuously prompt menu
	printf(MENU);
	scanf("%d", &option);
	while (1) {
		switch (option) {
			case 1:
				display_all(database, size);
				break;
			case 2:
				printf("Database contains %d sayings\n", size);
				break;
			case 3:
				display_sayings_with_word(database, size);
				break;
			case 4:
				enter_new_saying(database, &size);
				break;
			case 5:
				swap_two_sayings(database, size);
				break;
			case 6:
				save_database_to_file(database, size);
				break;
			case 7:
				return 0;
			default:
				printf("ERROR: Invalid option\n");
		}
		printf(MENU);
		scanf("%d", &option);
	}

	return 0;
}

// Loop through database and display all sayings
void display_all(char database[][MAX_SAYING_LENGTH], int size) {
	int i, j;
	for (i = 0; i < size; ++i) {
		printf("– %s\n", database[i]);
	}
}

// Loop through databse and display sayings that contain a substring (word)
void display_sayings_with_word(char database[][MAX_SAYING_LENGTH], int size) {
	char word[MAX_SAYING_LENGTH];

	printf("Enter word to search: ");
	scanf("%s", word);

	int i;
	for (i = 0; i < size; ++i) {
		if (strstr(database[i], word)) { // Check saying contains word
			printf("– %s\n", database[i]);
		}
	}
}

// Prompt user for new saying and enter into database
void enter_new_saying(char database[][MAX_SAYING_LENGTH], int *size) {
	char saying[MAX_SAYING_LENGTH];

	printf("Enter saying: ");
	fgetc(stdin); // Remove newline from stdin
	fgets(saying, MAX_SAYING_LENGTH, stdin); // Read saying (including whitespace)
	saying[strlen(saying) - 1] = '\0'; // Replace newline with null char
	strcpy(database[*size], saying);
	++*size; // Increment database size

	printf("Successfully inserted new saying\n");
}

// Swap positions of two sayings in database
void swap_two_sayings(char database[][MAX_SAYING_LENGTH], int size) {
	int swap1, swap2;
	char tmp[MAX_SAYING_LENGTH];

	printf("Enter index of first saying to swap (1 - %d): ", size);
	scanf("%d", &swap1);
	if (swap1 < 1 || swap1 > size) { // Ensure valid index 1
		printf("ERROR: Index %d does not exist in database\n", swap1);
		return;
	}

	printf("Enter index of second saying to swap (1 - %d): ", size);
	scanf("%d", &swap2);
	if (swap2 < 1 || swap2 > size) { // Ensure valid index 2
		printf("ERROR: Index %d does not exist in database\n", swap2);
		return;
	}

	// Perform swap
	strcpy(tmp, database[swap1 - 1]);
	strcpy(database[swap1 - 1], database[swap2 - 1]);
	strcpy(database[swap2 - 1], tmp);

	printf("Successfully swapped saying indices %d and %d\n", swap1, swap2);
}

// Save sayings databse to a file
void save_database_to_file(char database[][MAX_SAYING_LENGTH], int size) {
	FILE *fp;
	char filepath[MAX_FILEPATH];

	printf("Save database to file: ");
	scanf("%s", filepath);
	fp = fopen(filepath, "w");

	// Write to file
	int i;
	for (i = 0; i < size; ++i) {
		fputs(database[i], fp);
		fputc('\n', fp);
	}
	fclose(fp);

	printf("Successfully wrote database to %s\n", filepath);
}
