#include "stdio_impl.h"
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include "menuconfig.h"
#ifdef LOSCFG_LLTSER
#include "gcov_ser.h"
#endif
#include "fs/fs.h"
#include "fs/file.h"

FILE *fopen(const char *restrict filename, const char *restrict mode)
{
#ifdef LOSCFG_LLTSER
	GCOV_FOPEN(filename);
#endif
	FILE *f;
	int fd;
	int flags;

	/* Check for valid initial mode character */
	if (!strchr("rwa", *mode)) {
		errno = EINVAL;
		return 0;
	}

	/* Compute the flags to pass to open() */
	flags = __fmodeflags(mode);

	fd = open(filename, flags, 0666);
	if (fd < 0) return 0;
	if (flags & O_CLOEXEC)
		fcntl(fd, F_SETFD, FD_CLOEXEC);

#if !defined(__LP64__)
	if (fd > SHRT_MAX) {
		errno = EMFILE;
		return 0;
	}
#endif

	f = __fdopen(fd, mode);
	if (f) return f;

	close(fd);
	return 0;
}

weak_alias(fopen, fopen64);
