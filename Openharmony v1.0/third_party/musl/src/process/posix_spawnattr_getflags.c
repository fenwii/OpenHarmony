#include <spawn.h>
#include <unsupported_api.h>

int posix_spawnattr_getflags(const posix_spawnattr_t *restrict attr, short *restrict flags)
{
	unsupported_api(__FUNCTION__);
	*flags = attr->__flags;
	return 0;
}
