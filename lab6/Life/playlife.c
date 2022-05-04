// Eamon Tracey (etracey)
// FundComp Lab 6 playlife.c
//
// Run Game of Life in interactive or batch mode
//

#include "lifefunc.h"

int main(int argc, char *argv[]) {
	if (argc == 1) {
		play_interactive();
	} else if (argc == 2) {
		play_batch(argv[1]);
	} else {
		printf("ERROR: Too many arguments\n");
	}
}
