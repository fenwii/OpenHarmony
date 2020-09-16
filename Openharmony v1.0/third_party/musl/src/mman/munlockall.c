#include <sys/mman.h>
#include <unsupported_api.h>
#include "syscall.h"

int munlockall(void)
{
	unsupported_api(__FUNCTION__);
	return syscall(SYS_munlockall);
}
