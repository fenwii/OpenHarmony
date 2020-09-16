#include <unistd.h>
#include "libc.h"
#include "syscall.h"
#include "errno.h"

int setegid(gid_t egid)
{
	if (egid == -1) {
		errno = EINVAL;
		return -1;
	}
	return __setxid(SYS_setresgid, -1, egid, -1);
}
