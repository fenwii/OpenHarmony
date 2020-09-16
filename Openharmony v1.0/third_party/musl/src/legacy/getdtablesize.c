#define _GNU_SOURCE
#include <unistd.h>
#include <limits.h>
#include <sys/resource.h>
#include <unsupported_api.h>

int getdtablesize(void)
{
	struct rlimit rl;
	unsupported_api(__FUNCTION__);
	getrlimit(RLIMIT_NOFILE, &rl);
	return rl.rlim_cur < INT_MAX ? rl.rlim_cur : INT_MAX;
}
