#include <signal.h>
#include <unsupported_api.h>

void psiginfo(const siginfo_t *si, const char *msg)
{
	unsupported_api(__FUNCTION__);
	psignal(si->si_signo, msg);
}
