#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

#define MAX_THREADS 20

int isDivisible(int num, int divider) {
	if(num % divider == 0) return 1;
	return 0;
}

void writeToFile(int *ints, char *filename) {
	FILE *file = fopen(filename, "w");

	for(int i = 0; i < sizeof(ints); i++) fprintf(file, "%d ", ints[i]);

	fclose(file);
}

void* compute_d(void* params) {
	int *args = (int *) params;
	int ints[args[1]];
	int *d_count = (int*)malloc(sizeof(int));
	*d_count = 0;

	// filename = "numbers<thread_id>.txt"
	char filename[50];
	sprintf(filename, "numbers%d.txt", (int)pthread_self());

	FILE *file = fopen(filename, "w");

	for(int i = 0; i < args[1]; i++) {
		ints[i] = (rand() % (args[3] - (args[2] + 1))) + args[2];
		if(isDivisible(ints[i], args[4])) (*d_count)++;
		fprintf(file, "%d ", ints[i]);
	}

	fclose(file);
	return d_count;
}

int main(int argc, char *argv[]) {
	// handling passed arguments
	if(argc != 5) { printf("Unexpected numbers arguments.\nTerminating..\n"); exit(1); }

	int args[argc];

	for(int i = 1; i < argc; i++) args[i] = atoi(argv[i]);

	if(args[2] > args[3]) {
		int temp = args[2];
		args[2] = args[3];
		args[3] = temp;
	} else if (args[2] == args[3]) {
		printf("I can't create integers between same numbers: %d == %d\nTerminating..", args[2], args[3]);
		exit(1);
	}

	// setting up and starting threads
	pthread_t thread_ids[MAX_THREADS];
	int *results[MAX_THREADS];

	for(int i = 0; i < MAX_THREADS; i++) {
//		args[0] = i; beceremedik
		pthread_create(&thread_ids[i], NULL, compute_d, &args);
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
