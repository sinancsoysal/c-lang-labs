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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	if(argc != 3) {
		printf("Unexpected number of arguments.\nTerminating..\n");
		exit(1);
	}

	int limit = atoi(argv[2]);
	char filename[50], zipname[50];
	int status;
	pid_t p1, p2, p3;

	sprintf(filename, "%s.txt", argv[1]);
	sprintf(zipname, "%s.zip", argv[1]);

	printf("[PARENT] Creating first process...\n");
	p1 = fork();

	if(p1 == 0) {
		// We are int the first process

		FILE *file = fopen(filename, "w");

		printf("[CHILD1] Writing %d random char to %s\n", limit, filename);

		for(int i = 0; i < limit; i++) {
			char ch = rand() % ('z' - ('a' + 1)) + 1;
			fprintf(file, "%c\n", ch);
		}

		fclose(file);
	} else {
		wait(&status);
		printf("[PARENT] Creating second process...\n");
		p2 = fork();

		if(p2 == 0) {
			printf("[CHILD2] Executing zip command...\n");

			execl("/bin/zip", "zip", zipname, filename, NULL);

		} else {
			wait(&status);
			printf("[PARENT] Creating third process...\n");
			p3 = fork();

			if(p3 == 0) {

				printf("[CHILD3] Executing ls command...\n");
				execl("/bin/ls", "ls", NULL);

			} else {
				wait(&status);
				printf("[PARENT] Done.\n");
			}
		}
	}
}
