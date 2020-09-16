#include <sys/stat.h>
#include <unsupported_api.h>

int futimens(int fd, const struct timespec times[2])
{
	unsupported_api(__FUNCTION__);
	return utimensat(fd, 0, times, 0);
}
