#include <stdio.h>
#include <string.h>

#define MAX_WORD_LEN 100

int edit_dist(char word1[], char word2[]);

int main() {
	char word1[MAX_WORD_LEN], word2[MAX_WORD_LEN];
	
	fgets(word1, MAX_WORD_LEN, stdin);
	word1[strlen(word1) - 1] = '\0';
	fgets(word2, MAX_WORD_LEN, stdin);
	word2[strlen(word2) - 1] = '\0';

	printf("%d\n", edit_dist(word1, word2));

	return (0);
}

int edit_dist(char word1[], char word2[]) {
	/* YOUR CODE HERE */
	int n1 = strlen(word1);
	int n2 = strlen(word2);
	if (n1 == 0 || n2 == 0) {
		return n1+n2; // Edge case
	}
	//Dynamic Programming
	int dist[n1+1][n2+1];
	for (int i = 1; i <= n1; i++){
		for (int j = 1; j <= n2; j++){
			/*
			if (i == 0) {
				dist[i][j] == j; // Transforming an n-length string to an empty
				// string takes n operations
			}
			else if (j == 0) {
				dist[i][j] == i; // Transforming an n-length string to an empty
				// string takes n operations
			}
			else {
				dist[i][j] = 0;
			}
			*/
			dist[i][j] = 0;
		}
	}
	// Transforming an n-length string to an empty string takes n operations
	for (int i = 0; i <= n1; i++) {
		dist[i][0] = i;
	}
	for (int j = 0; j <= n2; j++) {
		dist[0][j] = j;
	}
	/*	//printing dist matrix
	for (int i = 0; i <= n1; i++) {
			for (int j = 0; j <= n2; j++) {
				printf("%d\t", dist[i][j]);
			}
			printf("\n");
	}
	*/

	int min = 0; // Variable for operation with minimum actions
	for (int i = 1; i <= n1; i++) {
		for (int j = 1; j <= n2; j++) {
			if (word1[i-1] == word2[j-1]) { // If there is a match
				dist[i][j] = dist[i-1][j-1];
			} else{
			// Three options: Replace, Insert, and Delete.
				int del = dist[i-1][j];
				int ins = dist[i][j-1];
				int rep = dist[i-1][j-1];

				if (del < ins) {
					min = del;
				} else {
					min = ins;
				}
				if (rep < min) {
					min = rep;
				}
				dist[i][j] = 1 + min;
			}
		}
	}
	/*	//printing dist matrix
	for (int i = 0; i <= n1; i++) {
		for (int j = 0; j <= n2; j++) {
			printf("%d\t", dist[i][j]);
		}
		printf("\n");
	}
	*/
	return dist[n1][n2];
}

