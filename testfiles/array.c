#include "../lib/lib.h"
int main () {
	int i;
	int array[10];

	for (i = 0; i < 10; i = i + 1) {
		array[i] = i;
	}
	for (i = 0; i < 10; i = i + 1) {
		printd (array[i]);
	}
	return 0;
}
