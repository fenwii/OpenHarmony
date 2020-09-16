#include <signal.h>
#include <errno.h>
#include <unsupported_api.h>

int killpg(pid_t pgid, int sig)
{
	unsupported_api(__FUNCTION__);
	if (pgid < 0) {
		errno = EINVAL;
		return -1;
	}
	return kill(-pgid, sig);
}
