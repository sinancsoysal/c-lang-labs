#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

#define MAX_THREADS 10

int is_prime(int n) {
	int flag = 1;

	if(n <= 1) return 0;
	else if (n == 2) return 1;

	for(int i = 2; i <= sqrt(n); i++) {
		if(n % i == 0) {
			flag = 0;
			break;
		}
	}

	return flag;
}

void *prime(void *params) {
	int size = *((int*) params);
	int numbers[size];
	int prime_count = 0;
	
	srand(time(0));
	
	for(int i = 0; i < sizeof(numbers); i++) {
		
		int random = (rand() % (9999-1000+1)) + 1000;
		numbers[i] = random;
		if(is_prime(numbers[i]) == 1) prime_count++;
	}
	
	printf("\nThread %lu - %d primes\n", pthread_self(), prime_count);
	
	pthread_exit(NULL);
	
}

int main( void ) {
	int number;

	for(int i = 0; i < MAX_THREADS; i++) { 
		pthread_t tid;
//		printf("Enter number: ");
//		scanf("%d", &number);	
		int size = 1000;
		pthread_create(&tid, NULL, prime, &size);
	}
	//pthread_exit(NULL);
}
