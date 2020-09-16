#include "stdio_impl.h"
#include "pthread_impl.h"
#include "los_futex_pri.h"

int __lockfile(FILE *f)
{
	int owner = f->lock, tid = pthread_self();
	if ((owner & ~MAYBE_WAITERS) == tid)
		return 0;
	owner = a_cas(&f->lock, 0, tid);
	if (!owner) return 1;
	while ((owner = a_cas(&f->lock, 0, tid|MAYBE_WAITERS))) {
		if ((owner & MAYBE_WAITERS) ||
		    a_cas(&f->lock, owner, owner|MAYBE_WAITERS)==owner)
			OsFutexWait((void *)&f->lock, FUTEX_WAIT, owner|MAYBE_WAITERS, 0xffffffffu);
	}
	return 1;
}

void __unlockfile(FILE *f)
{
	if (a_swap(&f->lock, 0) & MAYBE_WAITERS)
		OsFutexWake((void *)&f->lock, FUTEX_WAKE, 1);
}
