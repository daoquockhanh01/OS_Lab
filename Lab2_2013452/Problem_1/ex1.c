#include <stdio.h>
#include <stdint.h>
#include "ex1.h"

void *aligned_malloc(unsigned int size, unsigned int align) {
	if(size == 0)
		return NULL;
	void *ptr = NULL;
	ptr = malloc(size);
	intptr_t r = (intptr_t)ptr % (intptr_t)align;
	if(r != 0) {
		printf("\n");
		r = (r + size + 1072) % align; intptr_t x = align - r;
		void *k = malloc((unsigned int)x);
		void *ptr2 = malloc(size);
		free(ptr); free(k);
		return ptr2;
	}
	return ptr;
}

void *aligned_free(void *ptr) {
	free(ptr);
	return ptr;
}
