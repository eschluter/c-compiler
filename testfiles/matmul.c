#include "../lib/lib.h"
#define N 10

int main () {
	int i,j;
	int c[N];
	int b[N];
	int A[N][N];

	for (i = 0; i < N; i = i + 1) {
		b[i] = N - i;
	}
	for (i = 0; i < N; i = i + 1) {
		for (j = 0; j < N; j = j + 1) {
			A[i][j] = 5;
		}
	}

	// matrix vec multiply 
	for (i = 0; i < N; i = i + 1) {
		c[i] = 0;
		for (j = 0; j < N; j = j + 1) {
			c[i] = c[i] + A[i][j] * b[j];
		}
	}
	
	// print result
	printf ("b = \n");
	for (i = 0; i < N; i = i + 1) {
		printd(b[i]);
		printf ("\n");
	}
	printf ("\nA = \n");
	for (i = 0; i < N; i = i + 1) {
		for (j = 0; j < N; j = j + 1) {
			printd(A[i][j]);
			printf (" ");
		}
		printf ("\n");
	}
	printf ("\nc = \n");
	for (i = 0; i < N; i = i + 1) {
		printd(c[i]);
		printf ("\n");
	}
	return 0;
}
