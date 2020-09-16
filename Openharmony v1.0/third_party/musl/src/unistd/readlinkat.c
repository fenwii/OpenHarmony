#include <unistd.h>
#include <unsupported_api.h>

#include "syscall.h"

ssize_t readlinkat(int fd, const char *restrict path, char *restrict buf, size_t bufsize)
{
	unsupported_api(__FUNCTION__);
	return syscall(SYS_readlinkat, fd, path, buf, bufsize);
}
