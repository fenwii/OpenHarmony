#include <sys/stat.h>
#include "syscall.h"

int mkfifo(const char *path, mode_t mode)
{
	return syscall(SYS_mkfifo, path, mode);
}
