#include <sys/wait.h>
#include <unsupported_api.h>
#include "syscall.h"

int waitid(idtype_t type, id_t id, siginfo_t *info, int options)
{
	unsupported_api(__FUNCTION__);
	return syscall_cp(SYS_waitid, type, id, info, options, 0);
}
