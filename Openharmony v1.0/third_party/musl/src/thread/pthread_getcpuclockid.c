#include <unsupported_api.h>
#include "pthread_impl.h"

int pthread_getcpuclockid(pthread_t t, clockid_t *clockid)
{
	unsupported_api(__FUNCTION__);
	*clockid = (-t->tid-1)*8U + 6;
	return 0;
}
