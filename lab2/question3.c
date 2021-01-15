#include <signal.h>
#include <stdio.h>
#include <stdlib.h>


int number, flag;

void handleCtrlC(int signal){
	printf("\n");
	if(flag == 0) { flag = 1; printf("[Decreasing]\n"); }
	else { flag = 0; printf("[Increasing]\n"); }
}

int main() {
        signal(SIGINT, handleCtrlC);
	number = rand() % (200 - 101) + 100;

	printf("[Increasing]\n");
        while(1) {
		printf("Variable: %d\n", number);

		if(number < 100 || number > 200){
                        exit(0);
                }

                if(flag == 0) number += 10;
		else number -= 10;

		sleep(1);
        }
}
