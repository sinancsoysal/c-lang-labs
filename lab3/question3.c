#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if(argc != 5) {
		printf("Unexpected number of arguments.\nTerminating..\n");
		exit(1);
	}

	int limits[2] = {atoi(argv[3]), atoi(argv[4])};

	char *filename1 = argv[1], *filename2 = argv[2];
	int status;
	pid_t p1, p2, p3;

	printf("[PARENT] Creating first process...\n");
	p1 = fork();

	if(p1 == 0) {
		// We are int the first process

		FILE *file = fopen(filename1, "w");

		printf("[CHILD1] Writing %d random integers to %s\n", limits[0], filename1);

		for(int i = 0; i < limits[0]; i++) {
			int num = rand() % 100;
			fprintf(file, "%d\n", num);
		}

		fclose(file);
	} else {
		printf("[PARENT] Creating second process...\n");
		p2 = fork();

		if(p2 == 0) {

			FILE *file = fopen(filename2, "w");

			printf("[CHILD2] Writing %d random integers to %s\n", limits[1], filename2);

			for(int i = 0; i < limits[1]; i++) {
				int num = rand() % 100;
				fprintf(file, "%d\n", num);
			}

			fclose(file);

		} else {
			wait(&status);
			wait(&status);
			printf("[PARENT] Creating third process...\n");
			p3 = fork();

			if(p3 == 0) {
				wait(&status);
				printf("[CHILD3] Sorting both files...\n");
				execl("/bin/sort", "sort", "-n", "randfile1.txt", "randfile2.txt", NULL);

			} else {
				wait(&status);
				printf("[PARENT] Done.\n");
			}
		}
	}
}
