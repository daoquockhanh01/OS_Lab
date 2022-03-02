#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* hello(void* tid) {
	printf("Hello from thread %d\n", (int)tid);
	pthread_exit(NULL);
}

int main() {
	pthread_t tid[10];
	int i;
	for (int i = 0; i < 10; i++) {
		int rc = pthread_create(&tid[i], NULL, hello, (void*)i);
		if (rc) {
			printf("ERROR: Failed at: %d\n", i);
			exit(-1);
		}
		pthread_join(tid[i], NULL);
	}
	pthread_exit(NULL);
}
