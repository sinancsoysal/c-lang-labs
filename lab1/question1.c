#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
	if(argc > 3) { printf("Too many arguments supplied.\n"); }
	else if (argc == 3) {
      		FILE * fp;

		fp = fopen("numbers.txt", "w");
		srand(time(0));

		for(int i = 0; i < atoi(argv[1]); i++){
			for(int j = 0; j < atoi(argv[2]); j++){
				int num = rand() % (100 - 1);
				fprintf(fp, "%d\t", num);
			 }
			fprintf(fp, "\n");
		}

	} else { printf("Two arguments expected.\n"); }
}

