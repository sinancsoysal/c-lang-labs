#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
	FILE *fp;
	fp = fopen("numbers2.txt", "w");
	srand(time(0));

	for(int i = 0; i <= 1000; i++) {
		int num = (rand() % (1000 - 101)) + 100;
		fprintf(fp, "%d\n", num);
	}
}

