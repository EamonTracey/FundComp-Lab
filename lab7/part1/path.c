// Eamon Tracey (etracey)
// FundComp Lab 7 (1) path.c
//
// Parse arguments, call points.c pmain
//

#include <stdio.h>
#include "points.h"

#define MAX_FILEPATH_LENGTH 30

int main(int argc, char *argv[]) {
	if (argc == 2) {
		return pmain(argv[1]);
	} else {
		char filepath[MAX_FILEPATH_LENGTH];
		printf("Enter points filepath: ");
		scanf("%s", filepath);
		return pmain(filepath);
	}
}
