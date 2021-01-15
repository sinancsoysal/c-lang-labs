#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAXCHAR 100000

int main( void ) {
	pid_t child1, child2;
	int status;

	FILE* file;
	char str[MAXCHAR];
	char* filename = "data.txt";
	file = fopen(filename, "r");

	if(file == NULL) {
		printf("Couldn't open file %s", filename);
		return 1;
	}

	fgets(str, MAXCHAR, file);

	child1 = fork();

	if (child1 == 0) {
		int letters, i;
		letters = i = 0;
		while(str[i] != '\0') {
			if(str[i] >= 97 && str[i] <= 122) {
        	                letters++;
               		}
			i++;
		}
		printf("[CHILD1] Number of letters: %d\n", letters);
	} else {
		printf("[PARENT] Child process ID: %d\n",child1);
		child2 = fork();

		if (child2 == 0) {
			wait(&status);
			int numbers, i;
			while(str[i] != '\0') {
				if(str[i] >= 48 && str[i] <= 57) {
        	                	numbers++;
	               		}
				i++;
			}
			printf("[CHILD2] Number of numbers: %d\n", numbers);
		} else {
			wait(&status);
			printf("[PARENT] Child process ID: %d\n",child2);
		}
	}

	return 0;
}
