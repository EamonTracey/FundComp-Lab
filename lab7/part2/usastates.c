// Eamon Tracey (etracey)
// FundComp Lab 7 (2) usastates.c
//
// Parse arguments, call states.c smain 
//

#include <stdio.h>
#include "states.h"

#define MAX_FILEPATH_LENGTH 30

int main(int argc, char *argv[]) {
	if (argc == 2) {
		return smain(argv[1]);
	} else {
		char filepath[MAX_FILEPATH_LENGTH];
		printf("Enter states CSV filepath: ");
		scanf("%s", filepath);
		return smain(filepath);
	}
}
