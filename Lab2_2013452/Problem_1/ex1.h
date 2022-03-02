#ifndef _EX1_H_
#define _EX1_H_

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

void *aligned_malloc(unsigned int size, unsigned int align);

void *aligned_free(void *ptr);

#endif
