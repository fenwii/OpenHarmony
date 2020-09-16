#include "pthread_impl.h"
#include "lock.h"

int pthread_getschedparam(pthread_t t, int *restrict policy, struct sched_param *restrict param)
{
	int r;
	LOCK(t->killlock);
	if (!t->tid) {
		r = ESRCH;
	} else {
		r = __syscall(SYS_sched_getparam, t->tid, MUSL_TYPE_THREAD);
		if (r >= 0) {
			param->sched_priority = r;
			r = __syscall(SYS_sched_getscheduler, t->tid, MUSL_TYPE_THREAD);
			if (r >= 0) {
				*policy = r;
				r = 0;
			}
		}

		if (r < 0) {
			r = -r;
		}
	}
	UNLOCK(t->killlock);
	return r;
}
