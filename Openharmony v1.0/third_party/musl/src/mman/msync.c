#include <sys/mman.h>
#include <unsupported_api.h>
#include "syscall.h"

int msync(void *start, size_t len, int flags)
{
	unsupported_api(__FUNCTION__);
	return syscall_cp(SYS_msync, start, len, flags);
}
