#include <stdio.h>
#include "readline.h"

int read_line(char *str) {
	fgets(str, 50, stdin);
	int k = 0;
	while(str[k] != '\n') {
		if(str[k] < '0' || str[k] > '9') {
			if(k == 0 && str[k] == '-') {
				k++;
				continue;
			}
			return 0;
		}
		k++;
	}
	return 1;
}
