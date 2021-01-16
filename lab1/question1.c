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

