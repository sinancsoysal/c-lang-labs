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
#define DATA_SIZE 5000


// there is an error in this code
// some threads creates mess while counting
// generally first and second threads has problems but idk 

char vowels[] = "aeiou";

void* compute_chars(void *params) {
	char chars[DATA_SIZE];
	int vowel, consonant;

	for(int i = 0; i < DATA_SIZE; i++) {
		chars[i] = 'a' + (rand() % 26);
		if(strchr(&chars[i], *vowels) != NULL) vowel++;
		else consonant++;
	}

	pthread_t threadId = *((pthread_t*) params);
	printf("Thread %d: Vowels: %d, Consonants: %d\n", (int) threadId, vowel, consonant);
}

int main( void ) {
	pthread_t threadIds[MAX_THREADS];

	for(int i = 0; i < MAX_THREADS; i++) {
		if(pthread_create(&threadIds[i], NULL, compute_chars, &threadIds[i]) != 0) {
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



