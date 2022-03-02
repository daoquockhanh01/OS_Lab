// main.c
#include <stdio.h>
#include "readline.h"
#include "factorial.h"

int main(int argc, char *argv[]) {
	char str[50];
	if(read_line(str) == 0) 
		printf("%d \n", -1);
	else {
		int nums = 0, k = 0;
		while(str[k] != '\n') { 
			nums = nums * 10 + (int)(str[k] - '0');
			k++;
		}
		printf("%d \n", factorial(nums));
	}
	return 0;
}
