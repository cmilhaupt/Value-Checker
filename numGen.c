#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	int TOTAL_NUMBERS = 4000000;

	FILE * fp = fopen("numbers.txt", "w");
	time_t t;
	srand((unsigned) time(&t));
	
	for (int i = 0; i < TOTAL_NUMBERS; i++) {
		//print TOTAL_NUMBERS random numbers to a file
		//between 0 and 2^32 - 1
		fprintf(fp, "%d\n", rand());
	}
	return 0;
}
