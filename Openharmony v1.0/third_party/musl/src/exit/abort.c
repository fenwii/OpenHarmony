#include <stdlib.h>
#include <signal.h>
#include "syscall.h"
#include "pthread_impl.h"
#include "atomic.h"
#include "lock.h"
#include "ksigaction.h"

hidden volatile int __abort_lock[1];

_Noreturn void abort(void)
{
	sigset_t set, pending;
	sigemptyset(&set);
	sigaddset(&set, SIGABRT);

	sigpending(&pending);
	__syscall(SYS_rt_sigprocmask, SIG_UNBLOCK, &set, 0, _NSIG / 8);
	if (!sigismember(&pending, SIGABRT)) {
		raise(SIGABRT);
	}
	/* If there was a SIGABRT handler installed and it returned, or if
	 * SIGABRT was blocked or ignored, take an AS-safe lock to prevent
	 * sigaction from installing a new SIGABRT handler, uninstall any
	 * handler that may be present, and re-raise the signal to generate
	 * the default action of abnormal termination. */
	__block_all_sigs(0);
	LOCK(__abort_lock);
	signal(SIGABRT, SIG_DFL);
	__syscall(SYS_tkill, __pthread_self()->tid, SIGABRT);
	__syscall(SYS_rt_sigprocmask, SIG_UNBLOCK,
		&(long[_NSIG/(8*sizeof(long))]){1UL<<(SIGABRT-1)}, 0, _NSIG/8);

	/* Beyond this point should be unreachable. */
	a_crash();
	raise(SIGKILL);
	_Exit(127);
}
