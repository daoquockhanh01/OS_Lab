#include <stdio.h>
#include <stdlib.h>
#include "ex1.h"

int main() {
	int size = 0, align = 0;
	scanf("%d", &size); scanf("%d", &align);
	void *p = aligned_malloc(size, align);
	printf("%p\n", p);
	p = aligned_free(p);
	return 0;
}


