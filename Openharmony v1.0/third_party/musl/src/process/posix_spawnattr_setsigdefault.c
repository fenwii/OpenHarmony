#include <spawn.h>
#include <unsupported_api.h>

int posix_spawnattr_setsigdefault(posix_spawnattr_t *restrict attr, const sigset_t *restrict def)
{
	unsupported_api(__FUNCTION__);

	attr->__def = *def;
	return 0;
}
