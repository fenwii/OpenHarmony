#include <spawn.h>
#include <sched.h>
#include <errno.h>
#include <unsupported_api.h>

int posix_spawnattr_getschedparam(const posix_spawnattr_t *restrict attr,
	struct sched_param *restrict schedparam)
{
	unsupported_api(__FUNCTION__);
	return ENOSYS;
}

int posix_spawnattr_setschedparam(posix_spawnattr_t *restrict attr,
	const struct sched_param *restrict schedparam)
{
	unsupported_api(__FUNCTION__);
	return ENOSYS;
}

int posix_spawnattr_getschedpolicy(const posix_spawnattr_t *restrict attr, int *restrict policy)
{
	unsupported_api(__FUNCTION__);
	return ENOSYS;
}

int posix_spawnattr_setschedpolicy(posix_spawnattr_t *attr, int policy)
{
	unsupported_api(__FUNCTION__);
	return ENOSYS;
}
