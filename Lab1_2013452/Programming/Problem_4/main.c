#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
	FILE* input = NULL;
	char arr[128];
	int nums[100], k = 0, n2 = 0, n3 = 0;
	input = fopen("numbers.txt", "r");
	while(fgets(arr, 128, input) != NULL) {
		nums[k] = atoi(arr);
		k++;
	}
	fclose(input);
	pid_t pid = fork();
	if(pid < 0) {
		printf("Fork Failed\n");
		exit(0);
	}
	else if (pid == 0) {
		for(int i = 0; i < k; i++) 
			if(nums[i] % 3 == 0) 
				n3++;
		printf("%d \n", n3);
		exit(0);
	}
	for(int i = 0; i < k; i++) 
		if(nums[i] % 2 == 0)
			n2++;
	printf("%d \n", n2);
	return 0;
}
