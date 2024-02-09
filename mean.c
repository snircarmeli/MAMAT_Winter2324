#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mission(FILE *f);

int main(int argc, char *argv[]) {
	FILE *f;
	/* If no path was entered */
	if (argc == 1 || !strcmp(argv[1], "-")) {
		f = stdin;
	} else {
		f = fopen(argv[1], "r");
	}
	/* Checking that file exists */
	if (f == NULL) {
		fprintf(stderr, "Error, file does not found.");
		return 1;
	}
	mission(f);
}

void mission(FILE *f) {
	double sum = 0; /* sum of grades */
	int n = 0; /* number of grades */
	int grade;
	int val;
	double mean;
	
	while(1) {
		/* checking for numbers in file */
		val = fscanf(f, "%d", &grade);
		if (val == EOF) {
			break; /* End of file */
		} else if (val != 1) { /* Recieved more than one argument */
			fprintf(stderr, "Error, not a number\n");
			exit(1);
		}
		if (grade < 0 || grade > 100) {
			fprintf(stderr, "Error at line %d: grade %d invalid\n", n+1, grade);
			exit(1);
		}
		sum += grade;
		n += 1;
	}
	mean = sum/n;
	fprintf(stdout, "%.2f\n", mean);
}
