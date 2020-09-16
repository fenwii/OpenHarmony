#include <unistd.h>
#include <unsupported_api.h>

#include "syscall.h"

int fchownat(int fd, const char *path, uid_t uid, gid_t gid, int flag)
{
	unsupported_api(__FUNCTION__);
	return syscall(SYS_fchownat, fd, path, uid, gid, flag);
}
