#ifndef FSTOOLS_MALLOC_H
#define FSTOOLS_MALLOC_H 1

#include <stdlib.h>

static inline void* fst_xmalloc(unsigned long n) {
	void* p = malloc(n);
	if (p == NULL) {
		abort();
	}
	return p;
}

#endif