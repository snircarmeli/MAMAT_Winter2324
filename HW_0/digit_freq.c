// 123456789
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int main() {

    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
	char s[1000]={'a'};
	int hist[10]={0};
	scanf("%1000s", s);
	char z = '0';
	int offset;
	for (int i = 0; i < 1000; i++){
		offset=s[i]-z;
		if (offset <= 9 && offset >= 0)
			hist[offset]++;
		/* printf("%d\n", offset); */
	}
	for (int i = 0; i < 9; i++){
		printf("%d ", hist[i]);
	}
	printf("%d\n", hist[9]);
    /* return 0; */
}
