#include <sys/stat.h>
#include "syscall.h"
#include <unsupported_api.h>

int mknodat(int fd, const char *path, mode_t mode, dev_t dev)
{
	unsupported_api(__FUNCTION__);
	return syscall(SYS_mknodat, fd, path, mode, dev);
}
