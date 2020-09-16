#include "pthread_impl.h"

void __wait(volatile int *addr, volatile int *waiters, int val, int priv)
{
	int spins=100;

	while (spins-- && (!waiters || !*waiters)) {
		if (*addr==val) a_spin();
		else return;
	}
	if (waiters) a_inc(waiters);
	while (*addr==val) {
		__syscall(SYS_futex, addr, FUTEX_WAIT, val, 0xffffffffu);
	}
	if (waiters) a_dec(waiters);
}
