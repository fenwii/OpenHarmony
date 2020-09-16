#define _GNU_SOURCE
#include <sys/mman.h>
#include <unsupported_api.h>
#include "syscall.h"

int posix_madvise(void *addr, size_t len, int advice)
{
	unsupported_api(__FUNCTION__);
	if (advice == MADV_DONTNEED) return 0;
	return -__syscall(SYS_madvise, addr, len, advice);
}
