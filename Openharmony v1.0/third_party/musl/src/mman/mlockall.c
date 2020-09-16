#include <sys/mman.h>
#include <unsupported_api.h>
#include "syscall.h"

int mlockall(int flags)
{
	unsupported_api(__FUNCTION__);
	return syscall(SYS_mlockall, flags);
}
