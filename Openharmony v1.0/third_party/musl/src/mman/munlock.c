#include <sys/mman.h>
#include <unsupported_api.h>
#include "syscall.h"

int munlock(const void *addr, size_t len)
{
	unsupported_api(__FUNCTION__);
	return syscall(SYS_munlock, addr, len);
}
