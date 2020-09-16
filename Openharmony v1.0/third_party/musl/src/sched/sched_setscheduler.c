#include <sched.h>
#include <errno.h>
#include "syscall.h"
#include "pthread_impl.h"

int sched_setscheduler(pid_t pid, int sched, const struct sched_param *param)
{
	int r;
	if (!param) {
		r = -EINVAL;
		goto exit;
	}

	r = __syscall(SYS_sched_setscheduler, pid, sched, param->sched_priority, MUSL_TYPE_PROCESS);

exit:
	return __syscall_ret(r);
}
