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



