#include <fcntl.h>
#include <stdarg.h>
#include "syscall.h"
#include <unsupported_api.h>

int openat(int fd, const char *filename, int flags, ...)
{
	mode_t mode = 0;

	unsupported_api(__FUNCTION__);
	if ((flags & O_CREAT) || (flags & O_TMPFILE) == O_TMPFILE) {
		va_list ap;
		va_start(ap, flags);
		mode = va_arg(ap, mode_t);
		va_end(ap);
	}

	return syscall_cp(SYS_openat, fd, filename, flags|O_LARGEFILE, mode);
}

weak_alias(openat, openat64);
