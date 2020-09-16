#include <unistd.h>
#include <unsupported_api.h>

#include "syscall.h"

int fdatasync(int fd)
{
	unsupported_api(__FUNCTION__);
	return syscall_cp(SYS_fdatasync, fd);
}
