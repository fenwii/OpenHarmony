#include "pthread_impl.h"
#include "lock.h"

int pthread_setschedprio(pthread_t t, int prio)
{
	int r;

	if (prio < 0 || prio > PTHREAD_PRIORITY_LOWEST) {
		return EINVAL;
	}

	LOCK(t->killlock);
	r = !t->tid ? ESRCH : -__syscall(SYS_sched_setparam, t->tid, prio, MUSL_TYPE_THREAD);
	UNLOCK(t->killlock);
	return r;
}
