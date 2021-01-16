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
