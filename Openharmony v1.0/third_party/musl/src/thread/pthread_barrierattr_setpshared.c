#include <unsupported_api.h>
#include "pthread_impl.h"

int pthread_barrierattr_setpshared(pthread_barrierattr_t *a, int pshared)
{
	unsupported_api(__FUNCTION__);
	if (pshared > 1U) return EINVAL;
	a->__attr = pshared ? INT_MIN : 0;
	return 0;
}
