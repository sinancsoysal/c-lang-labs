#include <stdio.h>
 
#define MAXCHAR 100000
int main() {
	FILE *fp;
	char str[MAXCHAR];
	char* filename = "data.txt";
		 
	fp = fopen(filename, "r");
	if (fp == NULL){
		printf("Could not open file %s",filename);
		return 1;
	}

	int numc, letc, i;
	numc = letc = i = 0;	
	char ch;	

	fgets(str, MAXCHAR, fp);
  	while((ch = str[i]) != '\0') {
		//printf("%d", ch);
		if(ch >= '0' && ch <= '9') {
			numc++;
		} else if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')){
			letc++;
		}
		i++;
	}
	printf("l: %d\nn: %d\n", letc, numc);
	fclose(fp);
	return 0;
}
