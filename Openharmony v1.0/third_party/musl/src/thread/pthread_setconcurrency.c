#include <pthread.h>
#include <errno.h>
#include <unsupported_api.h>

int pthread_setconcurrency(int val)
{
	unsupported_api(__FUNCTION__);
	if (val < 0) return EINVAL;
	if (val > 0) return EAGAIN;
	return 0;
}
