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

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

#define MAX_THREADS 20

int *size;
int *numberOfLetters;
int *freq;
char *chars;

void* compute_f(void* params) {
	int thread_idx = *((int*) params);
//	int *freq = (int*) calloc(*numberOfLetters, sizeof(int));

	// filename = "numbers<thread_id>.txt"
	char filename[50];
	sprintf(filename, "chars%d.txt", thread_idx);

	FILE *file = fopen(filename, "w");

	for(int i = 0; i < *size; i++) {
		char ch = (rand() % *numberOfLetters) + chars[0];
		*(freq + (thread_idx * (*numberOfLetters)) + (ch - chars[0])) += 1;
		fprintf(file, "%c ", ch);
	}

	fclose(file);
	return (void*)freq;
}

int main(int argc, char *argv[]) {
	// handling passed arguments
	if(argc != 4) { printf("Unexpected numbers arguments.\nTerminating..\n"); exit(1); }

	size = (int*) malloc(sizeof(int));
	numberOfLetters = (int*) malloc(sizeof(int));
	chars = (char*) malloc(2 * sizeof(char));

	for(int i = 1; i < argc; i++) {
		if(i == 1) *size = atoi(argv[i]);
		else chars[i - 2] = argv[i][0];
	}

	if(chars[0] > chars[1]) {
		char temp = chars[0];
		chars[0] = chars[1];
		chars[1] = temp;
	} else if(chars[0] == chars[1]) {
		printf("I can't create chars between same chars: %c == %c\nTerminating..", chars[0], chars[1]);
		exit(1);
	}

	*numberOfLetters = (chars[1] - chars[0]) + 1;
	freq = (int *) calloc(*numberOfLetters * MAX_THREADS, sizeof(int));

//	printf("size = %d, nol = %d, ch1 = %c, ch2 = %c\n", *size, *numberOfLetters, chars[0], chars[1]);

	// setting up and starting threads
	pthread_t thread_ids[MAX_THREADS];
	int thread_idx[MAX_THREADS];
//	int **results = calloc(MAX_THREADS * (*numberOfLetters), sizeof(int*));

	// I couldn't figure out how to use 2d arrays in this operation
	// I created a single array that contains all the freq data

	for(int i = 0; i < MAX_THREADS; i++) {
		thread_idx[i] = i;
		if(pthread_create(&thread_ids[i], NULL, compute_f, &thread_idx[i]) != 0) {
			perror("error in thread creation");
			exit(1);
		}
	}

	// joining threads
	for(int i = 0; i < MAX_THREADS; i++) {
		if(pthread_join(thread_ids[i], NULL) != 0) {
			perror("error in thread join");
			exit(1);
		}
	}


	// print results
	for(int i = 0; i < MAX_THREADS; i++) {
		printf("Thread %d - ", i);
		for(int j = 0; j < *numberOfLetters; j++) {
			printf("%d ", *(freq + (*numberOfLetters * i) + j));
		}
		printf("\n");
	}

	free(size);
	free(numberOfLetters);
	free(freq);
	free(chars);
}
