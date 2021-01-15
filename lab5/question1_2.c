#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define MAX_THREADS 10
#define DATA_SIZE 10000

int *data;

int is_prime(int number) {
	if(number <= 1) return 0;
	else if(number == 2) return 1;

	if(number % 2 == 0 || number % 3 == 0) return 0;

	int flag = 1;

	for(int i = 5; i * i < number; i = i + 6) {
		if(number % i == 0 || number % (i + 2) == 0) { flag = 0; break; }
	}

	return flag;
}

void* prime(void *params) {
	int threadIdx = *((int*) params);
	// start index of this thread's data
	int start_idx = threadIdx * (DATA_SIZE/(double)MAX_THREADS);
	// end index of this thread's data
	int end_idx = (threadIdx + 1) * (DATA_SIZE/(double)MAX_THREADS);

	int prime_count = 0;

	for(int i = start_idx; i < end_idx; i++) {
		if(is_prime(data[i])) {
			prime_count++;
		}
	}

	printf("Thread %d - %d primes\n", threadIdx, prime_count);
}

int main( void ) {;
	data = (int*) calloc(DATA_SIZE, sizeof(int));

	// create a random integer array
	for(int i = 0; i < DATA_SIZE; i++) {
		data[i] = (rand() % (10000 - 1001) + 1000);
	}

	// create and start threads
	pthread_t threadIds[MAX_THREADS];
	int threadIdx[MAX_THREADS];

	for(int i = 0; i < MAX_THREADS; i++) {
		threadIdx[i]=i;
		if(pthread_create(&threadIds[i], NULL, prime, &threadIdx[i]) != 0) {
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



