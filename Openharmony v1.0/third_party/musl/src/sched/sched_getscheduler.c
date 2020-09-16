#include <sched.h>
#include <errno.h>
#include "syscall.h"
#include "pthread_impl.h"

int sched_getscheduler(pid_t pid)
{
	int r = __syscall(SYS_sched_getscheduler, pid, MUSL_TYPE_PROCESS);
	return __syscall_ret(r);
}
