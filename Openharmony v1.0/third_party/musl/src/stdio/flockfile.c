#include <unsupported_api.h>

#include "stdio_impl.h"
#include "pthread_impl.h"

void flockfile(FILE *f)
{
	unsupported_api(__FUNCTION__);
	if (!ftrylockfile(f)) return;
	__lockfile(f);
	__register_locked_file(f, __pthread_self());
}
