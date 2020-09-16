#include <sys/time.h>
#include <unsupported_api.h>
#include "fcntl.h"
#include "syscall.h"

int utimes(const char *path, const struct timeval times[2])
{
	unsupported_api(__FUNCTION__);
	return __futimesat(AT_FDCWD, path, times);
}
