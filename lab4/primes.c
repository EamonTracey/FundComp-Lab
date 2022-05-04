// Eamon Tracey (etracey)
// FundComp Lab 4 primes.c
//
// Find primes contained in [1, 1000]
//

#include <math.h>
#include <stdio.h>

int main() {
	int sieve[1001];
	
	int i, j;
	for (i = 0; i < 1001; ++i) {
		sieve[i] = 1;
	}

	for (i = 2; i < sqrt(1001) + 1; ++i) {
 		for (j = 2; j < 1001; ++j) {
			if (j == i) continue;
			if (j % i == 0) sieve[j] = 0;
		}
	}

	int c = 0;
	for (i = 2; i < 1001; ++i) {
		if (sieve[i] == 1) {
			printf("%3d ", i);
			if (++c % 10 == 0) printf("\n");
		}
	}
	printf("\n");

	return 0;
}
