#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

#define N 100
#define ll long long
#define ld long double
#define db double

int k = 0;
int p[N];
int seed[N];

void *PI(void *arg) {
	int i = *(int*)arg;
	//printf("index = %d\n", i);
	db x = 0, y = 0;
	for (int j = 0; j < k; j++) {
		x = (db)rand_r(&seed[i]) / (db)RAND_MAX;
		y = (db)rand_r(&seed[i]) / (db)RAND_MAX;
		db d = sqrt(x * x + y * y);
		if (d <= 1)
			p[i]++;
	}
	pthread_exit(NULL);
}

void main(int argc, char** argv) {
	int nPoints = atoi(argv[1]); k = nPoints / N;
	pthread_t threads[N];
	int a[N];
	srand(time(NULL));
	for (int i = 0; i < N; i++) {
		p[i] = 0;
		seed[i] = rand();

		/*
		int j = i;
		printf("Address is: %p\n", &j);
		int rc = pthread_create(&threads[i], NULL, PI, &j);
		*/

		a[i] = i;
		int rc = pthread_create(&threads[i], NULL, PI, &a[i]);

		if (rc) {
			printf("ERROR: failed at: %d\n", i);
			exit(-1);
		}
	}
	for (int i = 0; i < N; i++)
		pthread_join(threads[i], NULL);
	int sum = 0;
	for (int i = 0; i < N; i++)
		sum += p[i];
	ld pi = 4.0 * (ld)sum / (ld)nPoints;
	printf("%Lf\n", pi);
	pthread_exit(NULL);
}

