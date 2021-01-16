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
