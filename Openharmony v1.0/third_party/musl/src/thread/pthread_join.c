#define _GNU_SOURCE
#include "pthread_impl.h"
#include <sys/mman.h>

static void dummy1(pthread_t t)
{
}
weak_alias(dummy1, __tl_sync);

static int __pthread_timedjoin_np(pthread_t t, void **res, const struct timespec *at)
{
	int state, cs, r = 0;
	unsigned int tid;
	pthread_t self = __pthread_self();
	__pthread_testcancel();
	__pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &cs);
	if (cs == PTHREAD_CANCEL_ENABLE) __pthread_setcancelstate(cs, 0);
	if (t == self) {
		r = EINVAL;
		goto out;
	}

	switch (t->detach_state) {
		case DT_JOINABLE: {
			r = __syscall(SYS_pthread_join, t->tid);
			break;
		}
		case DT_EXITING:
			break;
		case DT_DETACHED:
		default:
			r = EINVAL;
			break;
	}

out:
	__pthread_setcancelstate(cs, 0);
	if (r == ESRCH || r == EINVAL) return r;
	__tl_sync(t);
	if (res) *res = t->result;
	tid = t->tid;
	t->tid = 0;
	return __syscall(SYS_pthread_deatch, tid);
}

int __pthread_join(pthread_t t, void **res)
{
	return __pthread_timedjoin_np(t, res, 0);
}

static int __pthread_tryjoin_np(pthread_t t, void **res)
{
	return t->detach_state==DT_JOINABLE ? EBUSY : __pthread_join(t, res);
}

weak_alias(__pthread_tryjoin_np, pthread_tryjoin_np);
weak_alias(__pthread_timedjoin_np, pthread_timedjoin_np);
weak_alias(__pthread_join, pthread_join);
