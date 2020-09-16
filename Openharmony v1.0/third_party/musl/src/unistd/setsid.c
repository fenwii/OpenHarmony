#include <unistd.h>
#include <unsupported_api.h>

#include "syscall.h"

pid_t setsid(void)
{
	unsupported_api(__FUNCTION__);
	return syscall(SYS_setsid);
}
