#include <stdlib.h>
#include <limits.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include "syscall.h"

char *realpath(const char *restrict filename, char *restrict resolved)
{
	int ret;
	char tmp[PATH_MAX];

	if (!filename) {
		errno = EINVAL;
		return 0;
	}

	ret = syscall(SYS_realpath, filename, tmp);
	if (ret < 0) return 0;

	return resolved ? strcpy(resolved, tmp) : strdup(tmp);
}
