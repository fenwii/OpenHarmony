#include <unistd.h>
#include <unsupported_api.h>

#include "syscall.h"

int symlinkat(const char *existing, int fd, const char *new)
{
	unsupported_api(__FUNCTION__);
	return syscall(SYS_symlinkat, existing, fd, new);
}
