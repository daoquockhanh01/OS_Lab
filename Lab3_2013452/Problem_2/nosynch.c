#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>

#define NUM_THREADS 3
#define TCOUNT 100
// with TCOUNT small (maybe < 10000000), this code almost doesn't
// result a race condition, since TCOUNT is small enougn!!!
// but with a bigger TCOUNT with no sleep after each loop,
// race condition may occur!!!
#define COUNT_LIMIT 20

int count = 10;
// pthread_mutex_t count_mutex;
// pthread_cond_t count_threshold_cv;

void * inc_count(void * tid) {
	int i;
	long my_id = (long)tid;
	for (i = 0; i < TCOUNT; i++) {
		// pthread_mutex_lock(&count_mutex);
		count++;
		if (count == COUNT_LIMIT) {
			printf("inc_count(): thread %ld, count = %d, threshold reached.\n", my_id, count);
			// pthread_cond_signal(&count_threshold_cv);
			printf("Just sent signal\n");
		}

		printf("inc_count(): thread %ld, count = %d, unlocking mutex\n", my_id, count);
		// pthread_mutex_unlock(&count_mutex);
		sleep(1);
	}
	pthread_exit(NULL);
}

void * watch_count(void * tid) {
	long my_id = (long)tid;
	printf("Starting watch_count(): thread %ld\n", my_id);

	// pthread_mutex_lock(&count_mutex);
	while (count < COUNT_LIMIT) {
		printf("watch_count(): thread %ld, count = %d, waiting...\n", my_id, count);
		// pthread_cond_wait(&count_threshold_cv, &count_mutex);
		printf("watch_count(): thread %ld. Condition signal received. Count = %d\n", my_id, count);
		printf("watch_count(): thread %ld. Updating the count value...\n", my_id);
		count += 80;
		printf("watch_count(): thread %ld count now = %d\n", my_id, count);
	}
	printf("watch_count(): thread %ld. Unlocking mutex.\n", my_id);
	// pthread_mutex_unlock(&count_mutex);
	pthread_exit(NULL);
}

int main(int argc, char ** argv) {
	int i, rc;
	pthread_t p1, p2, p3;
	long t1 = 1, t2 = 2, t3 = 3;

	// attr has no value in this code
	// because the default detach state of a thread is joinable
	// so don't need to set detach state to PTHREAD_CREATE_JOINABLE again
	// but ok, fine
	pthread_attr_t attr;

	printf("main: begin\n");
	// pthread_mutex_init(&count_mutex, NULL);
	// pthread_cond_init(&count_threshold_cv, NULL);

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

	pthread_create(&p1, &attr, watch_count, (void *)t1);
	pthread_create(&p2, &attr, inc_count, (void *)t2);
	pthread_create(&p3, &attr, inc_count, (void *)t3);

	rc = pthread_join(p1, NULL); assert (rc == 0);
	rc = pthread_join(p2, NULL); assert (rc == 0);
	rc = pthread_join(p3, NULL); assert (rc == 0);

	printf("main: finish, final count = %d\n", count);

	pthread_attr_destroy(&attr);
	// pthread_mutex_destroy(&count_mutex);
	// pthread_cond_destroy(&count_threshold_cv);
	pthread_exit(NULL);

	return 0;
}

