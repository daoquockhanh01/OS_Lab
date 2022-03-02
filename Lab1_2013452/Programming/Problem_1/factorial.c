#include "factorial.h"

int factorial (const int aNumber) {
	if (aNumber == 1)
		return 1;
	return aNumber * factorial(aNumber - 1);
}
