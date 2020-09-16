#include <unistd.h>
#include "syscall.h"
#include "libc.h"
#include "errno.h"

int seteuid(uid_t euid)
{
	if (euid == -1) {
		errno = EINVAL;
		return -1;
	}
	return __setxid(SYS_setresuid, -1, euid, -1);
}
