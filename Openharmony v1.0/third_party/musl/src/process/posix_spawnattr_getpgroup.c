#include <spawn.h>
#include <unsupported_api.h>

int posix_spawnattr_getpgroup(const posix_spawnattr_t *restrict attr, pid_t *restrict pgrp)
{
	unsupported_api(__FUNCTION__);
	*pgrp = attr->__pgrp;
	return 0;
}
