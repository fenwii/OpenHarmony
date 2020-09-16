#include "stdio_impl.h"
#include "pthread_impl.h"

#ifdef __GNUC__
__attribute__((__noinline__))
#endif
static int locking_putc(int c, FILE *f)
{
	if (a_cas(&f->lock, 0, MAYBE_WAITERS-1)) __lockfile(f);
	c = putc_unlocked(c, f);
	if (a_swap(&f->lock, 0) & MAYBE_WAITERS)
        OsFutexWake((void *)&f->lock, FUTEX_WAKE, 1);
	return c;
}

static inline int do_putc(int c, FILE *f)
{
	int l = f->lock;
	if (l < 0 || (l && (l & ~MAYBE_WAITERS) == pthread_self()))
		return putc_unlocked(c, f);
	return locking_putc(c, f);
}
