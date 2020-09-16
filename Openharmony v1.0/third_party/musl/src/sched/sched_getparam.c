#include <sched.h>
#include <errno.h>
#include <string.h>
#include "syscall.h"
#include "pthread_impl.h"

int sched_getparam(pid_t pid, struct sched_param *param)
{
	int r;
	if (!param) {
		r = -EINVAL;
		goto exit;
	}

	memset(param, 0, sizeof(struct sched_param));
	r = __syscall(SYS_sched_getparam, pid, MUSL_TYPE_PROCESS);
	if (r >= 0) {
		param->sched_priority = r;
		r = 0;
	}

exit:
	return __syscall_ret(r);
}
