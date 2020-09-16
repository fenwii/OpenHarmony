#ifndef UNSUPPORTED_API_H
#define UNSUPPORTED_API_H

#include <stdio.h>

static inline void unsupported_api(const char *func)
{
	fprintf(stderr, "[ERR]Unsupported API %s\n", func);
}

#endif
