#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>
#include "__dirent.h"
#include <unsupported_api.h>

DIR *fdopendir(int fd)
{
	DIR *dir;
	struct stat st;

	unsupported_api(__FUNCTION__);

	if (fstat(fd, &st) < 0) {
		return 0;
	}
	if (fcntl(fd, F_GETFL) & O_PATH) {
		errno = EBADF;
		return 0;
	}
	if (!S_ISDIR(st.st_mode)) {
		errno = ENOTDIR;
		return 0;
	}
	if (!(dir = calloc(1, sizeof *dir))) {
		return 0;
	}

	fcntl(fd, F_SETFD, FD_CLOEXEC);
	dir->fd = fd;
	return dir;
}
