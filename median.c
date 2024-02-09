#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int grade;
    struct Node *next;
};

void mission(FILE *f);
int median(int arr[], int n);
struct Node* createNode(int num);

int main(int argc, char *argv[]){
    FILE *f;
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
    //fprintf(stdout, "Good so far\n");
    mission(f);
}

struct Node* createNode(int num) {
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    if (node == NULL) {
        fprintf(stderr, "Memory failed.");
        exit(1);
    }
    node->grade = num;
    node->next = NULL;
    return node; 
}

void mission(FILE *f) {
    // Scanning the grades in file
    int cnt = 0;
    int val;
    int grade;
    struct Node *head = createNode(0);
    struct Node *N = head; //createNode(0);
    head->next = N;
    
    while (1) {
        val = fscanf(f, "%d", &grade);
		if (val == EOF) {
            N = NULL;
			break;
		}
		if (val != 1) { /* Recieved more than one argument */
			fprintf(stderr, "Error, not a number");
			exit(1);
		}	
		if (grade < 0 || grade > 100) {
			fprintf(stderr, "Error, not a valid grade in range of 0-100.");
			exit(1);
		}

        // Entering grades in a linked list
        N->grade = grade;
        struct Node *G = createNode(0); // Creating new node each time
        N->next = G;
        N = N->next;
        cnt++;
    }

    int grades[cnt]; // Creating an array for grades



    // Traversing the linked list
    struct Node *current = head;
    cnt = 0;
    while (current->next != NULL && current->grade != -1) {
        grades[cnt] = current->grade;
        cnt++;
        current = current->next;
    }
    free(head);
    free(current);
    int med = median(grades, cnt);
    fprintf(stdout, "%d\n", med);
}


int median(int arr[], int n) { 
    // Linear sorting
    int hist[101];
    int sorted[n];
    //int cumsum[101];
    for (int i = 0; i < 101; i++) {
        hist[i] = 0;
        //cumsum[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        hist[arr[i]]++;
    }
    /*
    //cumsum[0] = hist[0];
    //if (cumsum[0] >= n/2) {
    //    return arr[0];
    //}
    for (int i = 1; i < 101; i++) {
        cumsum[i] = cumsum[i-1]+hist[i];
        if (cumsum[i] >= n/2 + n%2) {
            return arr[i];
        }
    }  
    */
   int cnt = 0;
   for (int i = 0; i < 101; i++) {
        for (int j = 0; j < hist[i]; j++) {
            sorted[cnt] = i;
            //fprintf(stdout, "sorted[%d] = %d\n", cnt, sorted[cnt]);
            cnt++;
            
        }
   }
   return sorted[(n+1)/2-1];
    
}
