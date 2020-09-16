#include <stdio.h>
#include <unsupported_api.h>

#include "syscall.h"

int renameat(int oldfd, const char *old, int newfd, const char *new)
{
	unsupported_api(__FUNCTION__);
#ifdef SYS_renameat
	return syscall(SYS_renameat, oldfd, old, newfd, new);
#else
	return syscall(SYS_renameat2, oldfd, old, newfd, new, 0);
#endif
}
