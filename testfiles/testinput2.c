#include "../lib/lib.h"
int ii,jj,kk;
string first;

int integrate (int aa, int bb, int cc) {
	int local1, local2, local3;
	local1 = ii + bb - cc;
	local2 = 5 + 10 / jj;
	local3 = -bb % 2;
	printd (local1);
	printd (local2);
	printd (local3);
	return local1;
}

int main () {
	string second;
	ii = 98;
	jj = 3;
	kk = -13;

	if (ii > kk) {
		printd(ii);
	} else if (jj < kk) {
		printd(kk);
	} else {
		printd(jj);
	}
	
	if (ii > kk) {
		printd (kk);
	}
	
	if (ii < kk) {
		printd (jj);
	} else {
		jj = 3;
	}

	printd( integrate (56, 12, 13+1) );

	for (ii = 0; ii < 10; ii = ii + 1) {
		for (jj = 0; jj < 10; jj = jj + 1) {
			printd (jj+ii);
		}
	}
	printd (9999);
	ii = 0;
	while (ii < 10) {
		jj = jj + 1;
		printd (jj);
		ii = ii + 1;
	}
	printd (9999);
	ii = 0;
	first = "try this one on for size\n";
	do {
		jj = jj + 1;
		printd (jj);
		ii = ii + 1;
	} while (ii < 10);

	printf("This guy right here\n");
	printf (first);
	second = "oh idon'y noow\n";
	printf (second);

	if (first != second) {
		printf (first);
	} else {
		printf (second);
	}
	

	return 0;
}
