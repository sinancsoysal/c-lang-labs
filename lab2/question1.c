#include <signal.h>
#include <stdio.h>


int sum, count;

void handleCtrlC(int signal){
	printf("\nInputs: %d, Average: %d\n", count, sum/count);
	sum = 0;
	count = 0;
}

int main() {
	signal(SIGINT, handleCtrlC);
	while(1) {
		int number;
		printf("Enter a number: ");
		scanf("%d", &number);
		if(number == -1){
			printf("exitting..\n");
			exit(0);
		}
		count++;
		sum += number;
	}
}
