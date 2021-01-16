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

#define MAX_THREADS 10
#define DATA_SIZE 50000


char *vowels;
char *chars;

int isContains(char ch, char *string) {
	int i;
	for(i = 0; i < sizeof(*string) && string[i] != '\0'; i++) {
		if(ch == string[i]) return 1;
	}
	return 0;
}

void* compute_chars(void *params) {
	int thread_idx = *((int*) params);
	int start_idx = thread_idx * (DATA_SIZE/(double)MAX_THREADS);
	int end_idx = (thread_idx+1) * (DATA_SIZE/(double)MAX_THREADS);

	int vowel, consonant;

	for(int i = start_idx; i < end_idx; i++) {
		if(isContains(chars[i], vowels)) {
			vowel++;
		}
		else consonant++;
	}

	printf("Thread %d: Vowels: %d, Consonants: %d\n", (unsigned int) pthread_self(), vowel, consonant);
}

int main( void ) {
	vowels = (char*) calloc(DATA_SIZE, sizeof(char));
	vowels = "aeiou";

	chars = (char*) calloc(DATA_SIZE, sizeof(char));
	for(int i = 0; i < DATA_SIZE; i++) {
		chars[i] = 'a' + (rand() % 26);
	}

	pthread_t threadIds[MAX_THREADS];
	int threadIdx[MAX_THREADS];

	for(int i = 0; i < MAX_THREADS; i++) {
		threadIdx[i] = i;
		if(pthread_create(&threadIds[i], NULL, compute_chars, &threadIdx[i]) != 0) {
			perror("thread create");
			exit(1);
		}
	}

	for(int i = 0; i < MAX_THREADS; i++) {
		if(pthread_join(threadIds[i], NULL) != 0) {
			perror("thread join");
			exit(1);
		}
	}
}



