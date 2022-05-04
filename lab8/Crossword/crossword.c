// Eamon Tracey (etracey)
// FundComp Lab 8
//
// crossword.c
//

#include <stdio.h>
#include "crossfuncs.h"

int main(int argc, char *argv[]) {
	if (argc == 1) {
		// User entered no extra arguments

		return fcmain(stdin, stdout);
	} else if (argc == 2) {
		// User entered input filepath

		FILE *infp;

		infp = fopen(argv[1], "r");
		if (!infp) {
			printf("ERROR: File path %s does not exist\n", argv[1]);
			return -1;
		}

		return fcmain(infp, stdout);
	} else if (argc == 3) {
		// User entered input and output filepaths

		FILE *infp;
		FILE *outfp;
		
		infp = fopen(argv[1], "r");
		outfp = fopen(argv[2], "w");
		if (!infp) {
			fprintf(outfp, "ERROR: File path %s does not exist\n", argv[1]);
		}

		return fcmain(infp, outfp);
	} else {
		// User entered too many arguments

		printf("ERROR: Too many arguments (%d)\n", argc);
		return -1;
	}
}