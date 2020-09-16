#include "pthread_impl.h"
#include "lock.h"

int pthread_setschedparam(pthread_t t, int policy, const struct sched_param *param)
{
	int r;

	if (policy != SCHED_RR && policy != SCHED_FIFO) {
		return EINVAL;
	}

	if (param->sched_priority < 0 || param->sched_priority > PTHREAD_PRIORITY_LOWEST) {
		return EINVAL;
	}

	LOCK(t->killlock);
	r = !t->tid ? ESRCH : -__syscall(SYS_sched_setscheduler, t->tid, policy, param->sched_priority, MUSL_TYPE_THREAD);
	UNLOCK(t->killlock);
	return r;
}
