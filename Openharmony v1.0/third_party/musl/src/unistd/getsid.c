#include <unistd.h>
#include "syscall.h"
#include <unsupported_api.h>

pid_t getsid(pid_t pid)
{
	unsupported_api(__FUNCTION__);
	return syscall(SYS_getsid, pid);
}
