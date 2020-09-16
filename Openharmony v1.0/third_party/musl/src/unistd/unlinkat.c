#include <unistd.h>
#include <unsupported_api.h>

#include "syscall.h"

int unlinkat(int fd, const char *path, int flag)
{
	unsupported_api(__FUNCTION__);
	return syscall(SYS_unlinkat, fd, path, flag);
}
