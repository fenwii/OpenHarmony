#include <unistd.h>
#include <unsupported_api.h>

#include "syscall.h"

void sync(void)
{
	unsupported_api(__FUNCTION__);
	__syscall(SYS_sync);
}
