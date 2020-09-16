#include <spawn.h>
#include <unsupported_api.h>

int posix_spawnattr_setpgroup(posix_spawnattr_t *attr, pid_t pgrp)
{
	unsupported_api(__FUNCTION__);
	attr->__pgrp = pgrp;
	return 0;
}
