#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <math.h>
#include <semaphore.h>

#define N 100

int count = 0;
int nPoints = 0, k = 0;
int seed[N];

sem_t lock;
pthread_t tid[N];

void * PI(void * arg) {
	int i = *(int *)arg;
	double x = 0, y = 0;
	for (int j = 0; j < k; j++) {
		x = (double)rand_r(&seed[i]) / (double)RAND_MAX;
		y = (double)rand_r(&seed[i]) / (double)RAND_MAX;
		double d = sqrt(x * x + y * y);
		if (d <= 1) {
			sem_wait(&lock);
			count++;
			sem_post(&lock);
		}
	}
	pthread_exit(NULL);
}

int main(int argc, char ** argv) {
	if (argc < 2) {
		printf("ERROR: No argument!\n");
		exit(-1);
	}

	nPoints = atoi(argv[1]);
	k = nPoints / N;

	sem_init(&lock, 0, 1);

	srand(time(NULL));
	int arg[N];
	int rc;
	for (int i = 0; i < N; i++) {
		seed[i] = rand();
		arg[i] = i;
		rc = pthread_create(&tid[i], NULL, PI, &arg[i]);
		if (rc) {
			printf("ERROR: Failed at %d\n", i);
			exit(-1);
		}
	}

	for (int i = 0; i < N; i++) 
		pthread_join(tid[i], NULL);

	double pi = 4.0 * (double)count / (double)nPoints;
	printf("%f\n", pi);

	sem_destroy(&lock);

	return 0;
}
