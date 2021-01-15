#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

#define MAX_THREADS 20

int *args;

int isDivisible(int num, int divider) {
	if(num % divider == 0) return 1;
	return 0;
}

void* compute_d(void* params) {
	int thread_idx = *((int*) params);
	int *d_count = (int*)malloc(sizeof(int));
	*d_count = 0;

	// filename = "numbers<thread_id>.txt"
	char filename[50];
	sprintf(filename, "numbers%d.txt", thread_idx);

	FILE *file = fopen(filename, "w");

	for(int i = 0; i < args[1]; i++) {
		int num = (rand() % (args[2] - (args[1] + 1))) + args[1];
		if(isDivisible(num, args[3])) (*d_count)++;
		fprintf(file, "%d ", num);
	}

	fclose(file);
	return d_count;
}

int main(int argc, char *argv[]) {
	// handling passed arguments
	if(argc != 5) { printf("Unexpected numbers arguments.\nTerminating..\n"); exit(1); }

	args = (int*) malloc((argc - 1) * sizeof(int));

	for(int i = 1; i < argc; i++) args[i - 1] = atoi(argv[i]);

	if(args[1] > args[2]) {
		int temp = args[1];
		args[1] = args[2];
		args[2] = temp;
	} else if (args[1] == args[2]) {
		printf("I can't create integers between same numbers: %d == %d\nTerminating..", args[1], args[2]);
		exit(1);
	}

	// setting up and starting threads
	pthread_t thread_ids[MAX_THREADS];
	int thread_idx[MAX_THREADS];
	int *results[MAX_THREADS];

	for(int i = 0; i < MAX_THREADS; i++) {
		thread_idx[i] = i;
		pthread_create(&thread_ids[i], NULL, compute_d, &thread_idx[i]);
	}

	// joining threads
	for(int i = 0; i < MAX_THREADS; i++) {
		pthread_join(thread_ids[i], (void *)&results[i]);
	}

	// print results
	for(int i = 0; i < MAX_THREADS; i++) {
		printf("Thread %d - %d\n", i, *results[i]);
	}
}
