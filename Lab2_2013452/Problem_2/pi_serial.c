#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>

int main(int argc, char** argv) {
	int nPoints = atoi(argv[1]), ans = 0;
	double x = 0, y = 0;
	srand(time(NULL));
	for(int i = 0; i < nPoints; i++) {
		x = (double)rand() / (double)RAND_MAX;
		y = (double)rand() / (double)RAND_MAX;
		double d = sqrt(x * x + y * y);
		if(d <= 1) ans++;
	}
	double pi = 4.0 * (double)ans / (double)nPoints;
	printf("%f \n", pi);
	return 0;
}
