#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#define MAXCHAR 4

void generate_file(char* filename, int limit) {
	FILE* file = fopen(filename, "w");
	srand(time(0));

	for(int i = 0; i < limit; i++) {
		int random = rand() % 999;
		fprintf(file, "%d\n", random);
	}

	fclose(file);
}

void sort(char* filename) {
	execl("/bin/sort", "sort", "-n", filename, NULL);
}

int comp(const void* elem1, const void* elem2) {
	int f = *((int*)elem1);
	int s = *((int*)elem2);
	if (f > s) return  1;
	if (f < s) return -1;
	return 0;
}

void minmax(char* filename, int limit) {
	FILE* file = fopen(filename, "r");
	char str[MAXCHAR];
	int array[limit];

	if(file == NULL) { printf("couldn't open file: %s\n", filename); exit(1); }

	int i = 0, number;

	fscanf(file, "%d", &number);
	while(!feof(file)) {
		array[i] = number;
		i++;
		fscanf(file, "%d", &number);
	}

	fclose(file);

	qsort(array, sizeof(array)/sizeof(*array), sizeof(*array), comp);

	printf("Min: %d, Max: %d\n", array[0], array[limit-1]);
}

int main(int argc, char* argv[]) {
	char* filename;
	int limit;

	// check for supplies argument count
	if(argc == 3) {
		filename = argv[1];
		limit = atoi(argv[2]);
	} else {
		printf("[ERROR] usage: ./q1 <filename> <number of items>\n");
		exit(1);
	}

	pid_t p1, p2, p3;
	int status;

	printf("[PARENT] Creating first process...\n");
	p1 = fork();

	if(p1 == 0) {
		// We are in the first process
		// DONE create file and write random ints into file

		printf("[CHILD1] Creating %s with %d integers...\n", filename, limit);
		generate_file(filename, limit);
	} else {
		wait(&status);
		printf("[PARENT] Creating second process...\n");
		p2 = fork();

		if(p2 == 0) {
			// We are in the second process
			// DONE execute sort command

			printf("[CHILD2] Executing sort command...\n");
			sort(filename);
		} else {
			wait(&status);
			printf("[PARENT] Creating third process...\n");
			p3 = fork();

			if(p3 == 0) {
				// We are in the third process
				// DONE find min max

				printf("[CHILD3] ");
				minmax(filename, limit);
			} else {
				// We are in the parent process
				wait(&status);
				printf("[PARENT] Done.\n");
			}
		}
	}
}

