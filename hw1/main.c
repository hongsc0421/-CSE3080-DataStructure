#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void SWAP(char *x, char *y) {
	char temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void perm(char* list, int i, int n) {
	int j;

	if (i != n){
		for (j = i; j <= n; j++) {
			SWAP(&list[i], &list[j]);
			perm(list, i + 1, n);
			SWAP(&list[i], &list[j]);
		}
	}
}

int main() {
	int n;
	char list[12] = { 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108 };
	double duration;

	printf("     n    repetitions    time\n");
	for (n = 0; n <= 11; n++) {
		long repetitions = 0;
		clock_t start = clock();
		do {
			repetitions++;
			perm(list, 0, n);
		} while (clock() - start < 1000);

		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		duration /= repetitions;
		printf("%6d  %9d        %f\n", n, repetitions, duration);
	}
	

	return 0;
}