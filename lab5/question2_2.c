#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define MAX_THREADS 5
#define DATA_SIZE 10000

int *data;

int count_digits(int n) {
	int count = 0;
	while (n != 0) {
	       	n /= 10;
	        ++count;
    	}
	return count;
}

void* compute_digits(void *params) {
	int threadIdx = *((int*) params);
	// start index
	int start_idx = threadIdx * (DATA_SIZE/(double)MAX_THREADS);
	// end index
	int end_idx = (threadIdx + 1) * (DATA_SIZE/(double)MAX_THREADS);

	int digits[5];

	for(int i = start_idx; i < end_idx; i++) {
		switch(count_digits(data[i])) {
			case 1:
				digits[0]++;
				break;
			case 2:
				digits[1]++;
				break;
			case 3:
				digits[2]++;
				break;
			case 4:
				digits[3]++;
				break;
			case 5:
				digits[4]++;
				break;
		}
	}

	printf("Thread %d: 1-9: %d, 10-99: %d, 100-999: %d, 1000-9999: %d, 10000-99999: %d\n"
		,threadIdx, digits[0], digits[1], digits[2], digits[3], digits[4]);
}

int main( void ) {
	data = (int*) calloc(DATA_SIZE, sizeof(int));

	// create a random array
	for(int i = 0; i < DATA_SIZE; i++) {
		data[i] = rand() % (50000 - 1);
	}

	pthread_t threadIds[MAX_THREADS];
	int threadIdx[MAX_THREADS];

	for(int i = 0; i < MAX_THREADS; i++) {
		threadIdx[i]=i;
		if(pthread_create(&threadIds[i], NULL, compute_digits, &threadIdx[i]) != 0) {
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



