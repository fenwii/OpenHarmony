#include <unistd.h>
#include "syscall.h"
#include <unsupported_api.h>

int linkat(int fd1, const char *existing, int fd2, const char *new, int flag)
{
	unsupported_api(__FUNCTION__);
	return syscall(SYS_linkat, fd1, existing, fd2, new, flag);
}
