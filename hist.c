#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mission(FILE *f, int nbins);

int main(int argc, char *argv[]) {
	FILE *f;
	int n_bins;
	/* If no path was entered */
	if (argc == 1 || !strcmp(argv[1], "-")) {
		f = stdin;
	} else {
		f = fopen(argv[1], "r");
	}
	/* Checking that file exists */
	if (f == NULL) {
		fprintf(stderr, "Error, file does not found.\n");
		return 1;
	}

	/* Checking for argument -nbins. */
	for (int i = 0; i < argc; i++) {
		// If user wrote "-nbins"
		if (strcmp(argv[i], "-nbins") == 0) {
			if (i+1 < argc) {
				n_bins = atoi(argv[i+1]);
				if (n_bins <= 0) {
					fprintf(stderr, "Error, number of bins is illegal.\n");
					exit(1);
				}
			} else {
				n_bins = 10;
			}
			i = argc; // No number provided. Set to default.
		}
	}

	
	mission(f, n_bins);
}

void mission(FILE *f, int n_bins) {
	int hist[n_bins];
	int grade;
	int val;
	int bin;
	int n = 0;
	int lim[n_bins][2];
	int range = 101/n_bins;
	for (int i = 0; i < n_bins; i++) {
		hist[i] = 0;
	}
	lim[0][0] = 0;
	for (int i = 1; i < n_bins; i++) {
		lim[i-1][1] = lim[i-1][0]+range-1;
		lim[i][0] = lim[i-1][1]+1;
	}
	lim[n_bins-1][1] = 100;
	
	/* checking for numbers in file */
	
	while(1) {
		//fprintf(stdout, "number of bins atfer %d itterations is %d\n", n, n_bins);
		val = fscanf(f, "%d", &grade);
		if (val == EOF) {
			break;
		}
		//fprintf(stdout, "number of bins atfer %d itterations is %d\n", n, n_bins);
		if (val != 1) { /* Recieved more than one argument */
			fprintf(stderr, "Error, not a number");
			exit(1);
		}	
		//fprintf(stdout, "number of bins atfer %d itterations is %d\n", n, n_bins);
		if (grade < 0 || grade > 100) {
			fprintf(stderr, "Error, not a valid grade in range of 0-100.");
			exit(1);
		}
		//fprintf(stdout, "number of bins atfer %d iterations is %d\n", n, n_bins);
		bin = grade/range;
		if (bin >= n_bins-1) {
			bin = n_bins-1;
		}
		//fprintf(stdout, "Bin is %d\n", bin);
		hist[bin]++;
		n++;
		//fprintf(stdout, "number of bins atfer %d iterations is %d\n", n, n_bins);
	}
	//fprintf(stdout, "number of bins after while loop is %d\n", n_bins);
	for (int i = 0; i < n_bins; i++) {
		//fprintf(stdout, "hist[%d] is %d\n", i, hist[i]);
		fprintf(stdout,"%d-%d\t %d\n", lim[i][0], lim[i][1], hist[i]);
	}
}