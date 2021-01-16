/**
 * Copyright 2021 Sinan Can Soysal
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); 
 * you may not use this file except in compliance with the License. 
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, 
 * software distributed under the License is distributed on an "AS IS" BASIS, 
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
 * See the License for the specific language governing permissions and limitations under the License.
**/

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
