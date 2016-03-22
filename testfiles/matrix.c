#include "../lib/lib.h"

int main () {
	int i,j;
	int matrix[10][10];

	for (i = 0; i < 10; i = i + 1) {
		for (j = 0; j < 10; j = j + 1) {
			matrix[i][j] = j;
		}
	}
	for (i = 0; i < 10; i = i + 1) {
		printf ("\n");
		for (j = 0; j < 10; j = j + 1) {
			printd (matrix[i][j]);
		}
	}
	return 0;
}
