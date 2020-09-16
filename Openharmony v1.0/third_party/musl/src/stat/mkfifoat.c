#include <sys/stat.h>
#include <unsupported_api.h>

int mkfifoat(int fd, const char *path, mode_t mode)
{
	unsupported_api(__FUNCTION__);
	return mknodat(fd, path, mode | S_IFIFO, 0);
}
